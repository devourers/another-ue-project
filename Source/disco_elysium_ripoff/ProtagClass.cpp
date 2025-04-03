// Fill out your copyright notice in the Description page of Project Settings.


#include "ProtagClass.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NavMesh/RecastNavMesh.h"
#include "FadingActor.h"
#include "DrawDebugHelpers.h"
#include "PointAndClickPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationPath.h"
#include "Dialogue/DialogueUI.h"
#include "NiagaraFunctionLibrary.h"


// Sets default values
AProtagClass::AProtagClass()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	ProtagCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("ProtagCamera"));
	check(ProtagCameraComponent != nullptr);
	ProtagCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	ProtagCameraComponent->bUsePawnControlRotation = false;

	PathFinderComponent = CreateDefaultSubobject<UPathFollowingComponent>(TEXT("Pathfinder"));
	PathFinderComponent->Initialize();
	PathFinderComponent->SetStopMovementOnFinish(true);
	PathFinderComponent->OnRequestFinished.AddUFunction(this,FName("OnReachedPathDestinaton"));
	NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	SpringArmCollisionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxSpringArmCollision"));
	SpringArmCollisionVolume->SetupAttachment(CameraBoom);
	SpringArmCollisionVolume->SetCollisionProfileName("OverlapAll");
	SpringArmCollisionVolume->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	SpringArmCollisionVolume->SetCollisionObjectType(ECollisionChannel::ECC_Visibility);
	SpringArmCollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &AProtagClass::CameraBoomCollisionBegin);
	SpringArmCollisionVolume->OnComponentEndOverlap.AddDynamic(this, &AProtagClass::CameraBoomCollisionEnd);

	OcclusionHandler = CreateDefaultSubobject<UProtagOcclusionHandler>(TEXT("OcclusionHandler"));

	ProtagHUD = nullptr;
	ProtagHUDClass = nullptr;
}

void AProtagClass::CustomMoveToInteractable(AActor* actor) {
	if (NavSystem && PathFinderComponent) {
		TArray<AActor*> nav_mesh;
		ARecastNavMesh* vol = nullptr;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARecastNavMesh::StaticClass(), nav_mesh);
		if (nav_mesh.Num() == 1) {
			vol = Cast<ARecastNavMesh>(nav_mesh[0]);
		}
		IInteractable* casted_actor = Cast<IInteractable>(actor);
		UNavigationPath* u_path = NavSystem->FindPathToLocationSynchronously(this, 
			this->GetActorLocation(), 
			casted_actor->GetInteractionHitbox()->GetComponentLocation(),
			vol);

		if (u_path && !u_path->IsValid()) {
			//TODO: custom override if path is blocked by something
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString("Unreachable"));
			return;
		}

		if (u_path && u_path->IsValid() && !u_path->IsUnreachable()) {
			isMovingAlongPath = true;
			FAIMoveRequest request;
			request.SetAcceptanceRadius(0.0f);
			request.SetUsePathfinding(true);
			request.SetGoalLocation(casted_actor->GetInteractionHitbox()->GetComponentLocation());
			request.SetAllowPartialPath(false);
			request.SetRequireNavigableEndLocation(true);
			request.SetProjectGoalLocation(false);
			cached_actor = casted_actor;
			if (cached_actor && cached_actor->GetLogicComponent()->IsInteractionActive()) {
				cached_actor->OnInteractableSelectedAsDestination();
				FAIRequestID path_id = PathFinderComponent->RequestMove(request, u_path->GetPath());
				TArray<FVector> pts = u_path->PathPoints;
			}
		}
	}
}

void AProtagClass::CameraBoomCollisionBegin(
	class UPrimitiveComponent* HitComp, 
	class AActor* OtherActor, 
	class UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult) {
	AFadingActor* wall = Cast<AFadingActor>(OtherActor);
	if (wall) {
		++OcclusionCounter;
		isBehindWall = (OcclusionCounter > 0);
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString("Boom overlap " + OtherComp->GetClass()->GetFName().ToString()));
		wall->OnPlayerBehind();
	}

}

void AProtagClass::CameraBoomCollisionEnd(
	class UPrimitiveComponent* HitComp, 
	class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex) {
	AFadingActor* wall = Cast<AFadingActor>(OtherActor);
	if (wall) {
		--OcclusionCounter;
		isBehindWall = (OcclusionCounter > 0);
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString("Boom overlap end " + OtherComp->GetClass()->GetFName().ToString()));
		wall->OnPlayerNoLongerBehind();
	}
}

void AProtagClass::CustomMoveToLocation(const FVector& target_location) {
	if (NavSystem && PathFinderComponent) {
		TArray<AActor*> nav_mesh;
		ARecastNavMesh* vol = nullptr;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARecastNavMesh::StaticClass(), nav_mesh);
		if (nav_mesh.Num() == 1) {
			vol = Cast<ARecastNavMesh>(nav_mesh[0]);
		}
		//DrawDebugSphere(GetWorld(), target_location, 10, 10, FColor::Red, false, 5);
		UNavigationPath* u_path = NavSystem->FindPathToLocationSynchronously(this, this->GetActorLocation(), target_location, vol);
		
		if (u_path && !u_path->IsValid()) {
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString("Unreachable"));
			return;
		}
		if (u_path && u_path->IsValid() && !u_path->IsUnreachable()) {
			cached_actor = nullptr;
			isMovingAlongPath = true;
			FAIMoveRequest request;
			request.SetAcceptanceRadius(0.0f);
			request.SetUsePathfinding(true);
			request.SetAllowPartialPath(false);
			request.SetGoalLocation(target_location);
			request.SetProjectGoalLocation(false);
			request.SetRequireNavigableEndLocation(true);
			if (MoveToEffect != nullptr) {
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), MoveToEffect, target_location);
			}
			FAIRequestID path_id =  PathFinderComponent->RequestMove(request, u_path->GetPath());
			TArray<FVector> pts = u_path->PathPoints;
			//for (size_t i = 0; i < pts.Num(); ++i) {
			//	DrawDebugSphere(GetWorld(), pts[i], 10, 10, FColor::Green, false, 5);
			//	if (i + 1 != pts.Num()) {
			//		DrawDebugLine(GetWorld(), pts[i], pts[i + 1], FColor::Green, false, 5);
			//	}
			//}
		}
		
	}
}

void AProtagClass::StopPathfinderMovement() {
	if (isMovingAlongPath) {
		PathFinderComponent->RequestMoveWithImmediateFinish(EPathFollowingResult::Aborted);
		isMovingAlongPath = false;
	}
	
}

void AProtagClass::OnReachedPathDestinaton() {
	isMovingAlongPath = false;
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString("Request finished"));
	if (cached_actor)
		cached_actor->OnInteractableAsDestinationReached(this); //TODO: check for cached location? was it reached?
}

// Called when the game starts or when spawned
void AProtagClass::BeginPlay()
{
	Super::BeginPlay();

	controller_ = Cast<APointAndClickPlayerController>(GetController());
	if (controller_) {
		controller_->PlayerTargetLocationChanged.AddUniqueDynamic(this, &AProtagClass::OnPlayerTargerLocationChanged);
	}

	if (ProtagHUDClass) {
		APointAndClickPlayerController* PCC = GetController<APointAndClickPlayerController>();
		ProtagHUD = CreateWidget<UMainHUD>(PCC, ProtagHUDClass);
		ProtagHUD->AddToPlayerScreen();
	}
	
}

void AProtagClass::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	if (ProtagHUD) {
		ProtagHUD->RemoveFromParent();
		ProtagHUD = nullptr;
	}
	Super::EndPlay(EndPlayReason);

}

// Called every frame
void AProtagClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AProtagClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AProtagClass::UpdateLog(const FString& log_entry) {
	ProtagHUD->AddLogEntry(log_entry);
}

void AProtagClass::FadeCamera(bool FadeIn) {
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->FadeAmount = 1.0;
	if (FadeIn)
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraFade(0.0, 1.0, 1.0, FLinearColor::Black, false, true);
	else {
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StopCameraFade();
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraFade(1.0, 0.0, 1.0, FLinearColor::Black, false);
	}

}

void AProtagClass::FadeOutAfterTeleport() {
	FadeCamera(false);
}

bool AProtagClass::IsBehindWall() const {
	return isBehindWall;
}

void AProtagClass::InitDialogueWindow(UDialogueUI* ui){
	//todo: hide other Ui, or spawn at some point of main hud
	ProtagHUD->SetVisibility(ESlateVisibility::Hidden);
	DisableProtagInput();
	ui->AddToPlayerScreen();
}

void AProtagClass::UnhideHUD(){
	ProtagHUD->SetVisibility(ESlateVisibility::Visible);
}

void AProtagClass::OnPlayerTargerLocationChanged(const FVector& NewLocation){

}

void AProtagClass::DisableProtagInput(){
	controller_->DisableInput(controller_);
}

void AProtagClass::EnableProtagInput(){
	controller_->EnableInput(controller_);
}
