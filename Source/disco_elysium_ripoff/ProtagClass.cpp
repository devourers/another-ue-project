// Fill out your copyright notice in the Description page of Project Settings.


#include "ProtagClass.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NavMesh/RecastNavMesh.h"
#include "FadingActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationPath.h"


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
}

void AProtagClass::CustomMoveToInteractableActor(AActor* actor) {
	if (NavSystem && PathFinderComponent) {
		TArray<AActor*> nav_mesh;
		ARecastNavMesh* vol = nullptr;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARecastNavMesh::StaticClass(), nav_mesh);
		if (nav_mesh.Num() == 1) {
			vol = Cast<ARecastNavMesh>(nav_mesh[0]);
		}
		UNavigationPath* u_path = NavSystem->FindPathToActorSynchronously(this, this->GetActorLocation(), actor, 100, vol);

		if (u_path && !u_path->IsValid()) {
			//TODO: custom override if path is blocked by something
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString("Unreachable"));
			return;
		}

		if (u_path && u_path->IsValid()) {
			isMovingAlongPath = true;
			FAIMoveRequest request;
			request.SetAcceptanceRadius(10);
			request.SetUsePathfinding(true);
			request.SetGoalActor(actor);
			cached_actor = Cast<AInteractableActor>(actor);
			cached_actor->OnActorSelectedAsDestination();
			FAIRequestID path_id = PathFinderComponent->RequestMove(request, u_path->GetPath());
			TArray<FVector> pts = u_path->PathPoints;
			for (size_t i = 0; i < pts.Num(); ++i) {
				DrawDebugSphere(GetWorld(), pts[i], 10, 10, FColor::Green, false, 5);
				if (i + 1 != pts.Num()) {
					DrawDebugLine(GetWorld(), pts[i], pts[i + 1], FColor::Green, false, 5);
				}
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
	isBehindWall = true;
	AFadingActor* wall = Cast<AFadingActor>(OtherActor);
	if (wall) {
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString("Boom overlap " + OtherComp->GetClass()->GetFName().ToString()));
		wall->OnPlayerBehind();
	}

}

void AProtagClass::CameraBoomCollisionEnd(
	class UPrimitiveComponent* HitComp, 
	class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex) {
	isBehindWall = false;
	AFadingActor* wall = Cast<AFadingActor>(OtherActor);
	if (wall) {
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
		DrawDebugSphere(GetWorld(), target_location, 10, 10, FColor::Red, false, 5);
		UNavigationPath* u_path = NavSystem->FindPathToLocationSynchronously(this, this->GetActorLocation(), target_location, vol);
		
		if (!u_path->IsValid()) {
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString("Unreachable"));
			return;
		}
		if (u_path && u_path->IsValid()) {
			cached_actor = nullptr;
			isMovingAlongPath = true;
			FAIMoveRequest request;
			request.SetAcceptanceRadius(10);
			request.SetUsePathfinding(true);
			request.SetGoalLocation(target_location);
			request.SetRequireNavigableEndLocation(true);
			FAIRequestID path_id =  PathFinderComponent->RequestMove(request, u_path->GetPath());
			TArray<FVector> pts = u_path->PathPoints;
			for (size_t i = 0; i < pts.Num(); ++i) {
				DrawDebugSphere(GetWorld(), pts[i], 10, 10, FColor::Green, false, 5);
				if (i + 1 != pts.Num()) {
					DrawDebugLine(GetWorld(), pts[i], pts[i + 1], FColor::Green, false, 5);
				}
			}
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
		cached_actor->OnActorAsDestinationReached(this);
}

// Called when the game starts or when spawned
void AProtagClass::BeginPlay()
{
	Super::BeginPlay();
	
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

