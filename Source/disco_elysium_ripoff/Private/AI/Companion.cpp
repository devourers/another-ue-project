// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Companion.h"
#include "AI/CompanionAIController.h"
#include "../PointAndClickPlayerController.h"
#include "../ProtagClass.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACompanion::ACompanion()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetupAttachment(GetRootComponent());

	GetMesh()->OnBeginCursorOver.AddDynamic(this, &ACompanion::OnCursorOver);
	GetMesh()->OnEndCursorOver.AddDynamic(this, &ACompanion::OnCursorEnd);
	GetMesh()->SetRenderCustomDepth(false);
	GetMesh()->SetCustomDepthStencilValue(STENCIL_UNLOCKED_DOOR);

	InteractionHitbox = CreateDefaultSubobject<USphereComponent>(TEXT("Interaction Collision"));
	InteractionHitbox->SetCanEverAffectNavigation(false);
	InteractionHitbox->SetupAttachment(GetMesh());
	InteractionHitbox->SetGenerateOverlapEvents(true);
	InteractionHitbox->SetCollisionProfileName("NoCollision");
	InteractionHitbox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionHitbox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	LogicComponent = CreateDefaultSubobject<ULogicComponent>(TEXT("Logic Component"));
}

// Called when the game starts or when spawned
void ACompanion::BeginPlay()
{
	Super::BeginPlay();
	
	AController* self_controller = GetController();
	controller_ = Cast<ACompanionAIController>(self_controller);

	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	APointAndClickPlayerController* casted_controller = Cast<APointAndClickPlayerController>(controller);
	if (casted_controller) {
		casted_controller->PlayerDoubleClicked.AddUniqueDynamic(this, &ACompanion::OnPlayerDoubleClicked);
	}
}

void ACompanion::ToggleHighlight(bool to_toggle){
	GetMesh()->SetRenderCustomDepth(to_toggle);
}

void ACompanion::InternalInteract(AActor* other_actor){
	//TODO
}

void ACompanion::OnCursorOver(UPrimitiveComponent* Component){
	ToggleHighlight(true);
}

void ACompanion::OnCursorEnd(UPrimitiveComponent* Component){
	ToggleHighlight(false);
}

void ACompanion::OnInteractableAsDestinationReached(AActor* other_actor){
	SetIsSelectedAsDestination(false);
	GetMesh()->SetRenderCustomDepth(false);
	Interact(other_actor);
}

void ACompanion::OnInteractableSelectedAsDestination(){
	SetIsSelectedAsDestination(true);
	GetMesh()->SetRenderCustomDepth(true);
}

USphereComponent* ACompanion::GetInteractionHitbox()
{
	return InteractionHitbox;
}

ULogicComponent* ACompanion::GetLogicComponent()
{
	return LogicComponent;
}

UMainGameInstanceSubsystem* ACompanion::GetHandler()
{
	return handler_;
}

AProtagClass* ACompanion::GetProtag()
{
	return protag_;
}

void ACompanion::BindProtag(AActor* other_actor){
	protag_ = Cast<AProtagClass>(other_actor);
}

// Called every frame
void ACompanion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACompanion::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACompanion::OnPlayerDoubleClicked(bool didDoubleClick) {
	if (didDoubleClick)
		GetCharacterMovement()->MaxWalkSpeed = 590.0f;
	else
		GetCharacterMovement()->MaxWalkSpeed = 295.0f;
}