// Fill out your copyright notice in the Description page of Project Settings.


#include "PointAndClickPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Engine/World.h"
#include "Engine/LocalPlayer.h"
#include "FadingActor.h"
#include "Kismet/GameplayStatics.h"
#include "InteractableActor.h"
#include "ProtagClass.h"

APointAndClickPlayerController::APointAndClickPlayerController() {
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void APointAndClickPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void APointAndClickPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(HighlightAllIntercatbleActors, ETriggerEvent::Started, this, &APointAndClickPlayerController::OnHighlightAllIntercatbleActors);
		EnhancedInputComponent->BindAction(HighlightAllIntercatbleActors, ETriggerEvent::Completed, this, &APointAndClickPlayerController::OnEndHighlightAllIntercatbleActors);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &APointAndClickPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &APointAndClickPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &APointAndClickPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &APointAndClickPlayerController::OnSetDestinationReleased);
	}
}

void APointAndClickPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void APointAndClickPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();

	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;

	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
		AInteractableActor* casted_actor = Cast<AInteractableActor>(Hit.GetActor());
		CachedActor = casted_actor;
		if (casted_actor)
			isCachedActorInteractible = true;
		else
			isCachedActorInteractible = false;
	}

	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	AFadingActor* wall = Cast<AFadingActor>(Hit.GetActor());
	if (wall)
		clickedOnWall = true;
	else
		clickedOnWall = false;
	if (ControlledPawn != nullptr && !clickedOnWall)
	{
		AProtagClass * protag = Cast<AProtagClass>(ControlledPawn);
		protag->StopPathfinderMovement();
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void APointAndClickPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		APawn* ControlledPawn = GetPawn();
		AProtagClass* protag = Cast<AProtagClass>(ControlledPawn);
		// We move there and spawn some particles
		if (isCachedActorInteractible) {
			protag->CustomMoveToInteractableActor(CachedActor);
		}
		else if (!clickedOnWall){
			protag->CustomMoveToLocation(CachedDestination);
		}
	}

	FollowTime = 0.f;
}

void APointAndClickPlayerController::OnHighlightAllIntercatbleActors() {
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString("Triggered"));
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AInteractableActor::StaticClass(), actors);
	for (AActor* actor : actors) {
		AInteractableActor* casted_actor = Cast<AInteractableActor>(actor);
		casted_actor->OnActorSelectedAsDestination();
	}
}

void APointAndClickPlayerController::OnEndHighlightAllIntercatbleActors() {
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString("Finished Trigger"));
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AInteractableActor::StaticClass(), actors);
	for (AActor* actor : actors) {
		AInteractableActor* casted_actor = Cast<AInteractableActor>(actor);
		APawn* ControlledPawn = GetPawn();
		AProtagClass* protag = Cast<AProtagClass>(ControlledPawn);
		casted_actor->OnActorAsDestinationReached(protag);
	}
}