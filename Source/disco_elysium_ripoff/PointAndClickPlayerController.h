// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Public/Interactable.h"
#include "PointAndClickPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API APointAndClickPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	APointAndClickPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold = 0.3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SetDestinationClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* HighlightAllIntercatbleActors;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAcess = "true"))
	UInputAction* DoubleClick;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;

	// To add mapping context
	virtual void BeginPlay();

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnHighlightAllIntercatbleActors();
	void OnEndHighlightAllIntercatbleActors();
	void OnDoubleClickTriggered();

private:
	FVector CachedDestination;
	AActor* CachedActor;
	bool isCachedActorInteractible;
	bool clickedOnWall;
	bool DoubleClicked = false;
	float FollowTime; // For how long it has been pressed
};
