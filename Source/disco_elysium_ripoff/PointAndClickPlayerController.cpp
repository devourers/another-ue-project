// Fill out your copyright notice in the Description page of Project Settings.


#include "PointAndClickPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Engine/World.h"
#include "Engine/LocalPlayer.h"
#include "FadingActor.h"
#include "Kismet/GameplayStatics.h"
#include "ProtagClass.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Utils/DERSaveGame.h>
#include <Utils/SaveLoadGameInstanceSubsystem.h>

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
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn) {
		LastBroadcastedLocation = ControlledPawn->GetActorLocation();
	}
	PauseMenuUI = CreateWidget<UPauseMenuUI>(this, PauseMenuUIClass);
	if (PauseMenuUI) {
		PauseMenuUI->BindController(this);
		PauseMenuUI->AddToViewport();
		PauseMenuUI->SetVisibility(ESlateVisibility::Hidden);
		PauseMenuUI->PauseMenuUIButtonPressed.AddUniqueDynamic(this, &APointAndClickPlayerController::HandleMenuPress);
	}
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
		EnhancedInputComponent->BindAction(DoubleClick, ETriggerEvent::Completed, this, &APointAndClickPlayerController::OnDoubleClickTriggered);
		EnhancedInputComponent->BindAction(PausePress, ETriggerEvent::Triggered, this, &APointAndClickPlayerController::OnPausePressed);
	}
}

void APointAndClickPlayerController::OnPossess(APawn* aPawn){
	Super::OnPossess(aPawn);
	protag_ = Cast<AProtagClass>(aPawn); //this should never fail, if it did something really bad happened
}

void APointAndClickPlayerController::OnInputStarted()
{
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString("Started"));
	StopMovement();
}

// Triggered every frame when the input is held down
void APointAndClickPlayerController::OnSetDestinationTriggered()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString("Triggered"));
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

		IInteractable* casted_actor = Cast<IInteractable>(Hit.GetActor());
		if (casted_actor) {
			CachedActor = Hit.GetActor();
			CachedDestination = casted_actor->GetInteractionHitbox()->GetComponentLocation();
			isCachedActorInteractible = true;
		}
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
		if (FollowTime <= ShortPressThreshold) {
			protag_->StopPathfinderMovement();
		}
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void APointAndClickPlayerController::OnSetDestinationReleased()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString("Released"));
	// If it was a short press

	if (FollowTime <= ShortPressThreshold)
	{
		if (DoubleClicked) {
			protag_->GetCharacterMovement()->MaxWalkSpeed = 600;
			DoubleClicked = false;
		}
		else {
			protag_->GetCharacterMovement()->MaxWalkSpeed = 300;
			PlayerDoubleClicked.Broadcast(false);
		}
		// We move there and spawn some particles
		if (isCachedActorInteractible) {
			protag_->CustomMoveToInteractable(CachedActor);
		}
		else if (!clickedOnWall){
			protag_->CustomMoveToLocation(CachedDestination);
		}
		if ((CachedDestination - LastBroadcastedLocation).Length() > distance_update_threshold_) {
			PlayerTargetLocationChanged.Broadcast(CachedDestination);
			LastBroadcastedLocation = CachedDestination;
		}
	}

	FollowTime = 0.f;
}

void APointAndClickPlayerController::OnHighlightAllIntercatbleActors() {
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UInteractable::StaticClass(), actors);
	for (AActor* actor : actors) {
		IInteractable* casted_actor = Cast<IInteractable>(actor);
		casted_actor->ToggleHighlight(true);
	}
}

void APointAndClickPlayerController::OnEndHighlightAllIntercatbleActors() {
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UInteractable::StaticClass(), actors);
	for (AActor* actor : actors) {
		IInteractable* casted_actor = Cast<IInteractable>(actor);
		if (!casted_actor->IsSelectedAsDestination())
			casted_actor->ToggleHighlight(false);
	}
}

void APointAndClickPlayerController::OnDoubleClickTriggered() {
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString("Double click"));

	//FollowTime += GetWorld()->GetDeltaSeconds();
	if (FollowTime <= ShortPressThreshold) {
		protag_->StopPathfinderMovement();
	}
	PlayerDoubleClicked.Broadcast(true);
	DoubleClicked = true;
	OnSetDestinationReleased();
}

void APointAndClickPlayerController::OnPausePressed() {
	if (!IsPaused()) {
		SetPause(true);
		protag_->HideHUD();
		PauseMenuUI->SetVisibility(ESlateVisibility::Visible);
	}
		
	else {
		SetPause(false);
		protag_->UnhideHUD();
		PauseMenuUI->SetVisibility(ESlateVisibility::Hidden);
	}
}

void APointAndClickPlayerController::HandleMenuPress(const FString& key) {
	if (key.Equals(FString("Continue"))) {
		SetPause(false);
		protag_->UnhideHUD();
		PauseMenuUI->SetVisibility(ESlateVisibility::Hidden); //TODO
	}
	else if (key.Equals(FString("MainMenu"))){
		UGameplayStatics::OpenLevel(GetWorld(), FName("/Game/Levels/MainMenu/L_MainMenu1"));
	}
	else if (key.Equals(FString("SaveGame"))) {
		USaveLoadGameInstanceSubsystem* SGS = GetGameInstance()->GetSubsystem<USaveLoadGameInstanceSubsystem>();
		SGS->WriteSaveGame("TestFromPause");
		protag_->UpdateLog("Game saved.");
	}
	else if (key.Equals(FString("LoadGame"))) {
		USaveLoadGameInstanceSubsystem* SGS = GetGameInstance()->GetSubsystem<USaveLoadGameInstanceSubsystem>();
		SGS->LoadSaveGame("TestFromPause");
		protag_->UpdateLog("Game Loaded");
	}
}