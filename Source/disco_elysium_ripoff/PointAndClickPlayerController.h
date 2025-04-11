// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Public/Interactable.h"

#include "Public/UI/PauseMenuUI.h"

#include "PointAndClickPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerTargetLocationChanged, const FVector&, NewLocation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerDoubleClicked, bool, didDoubleClick);

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAcess = "true"))
	UInputAction* PausePress;

	UPROPERTY()
	FPlayerTargetLocationChanged PlayerTargetLocationChanged;
	
	UPROPERTY()
	FPlayerDoubleClicked PlayerDoubleClicked;


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
	void OnPausePressed();

	UFUNCTION()
	void HandleMenuPress(const FString& key);

private:
	UPROPERTY()
	class UPauseMenuUI* PauseMenuUI;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UPauseMenuUI> PauseMenuUIClass;

private:
	double distance_update_threshold_ = 300.0f;
	FVector LastBroadcastedLocation;
	FVector CachedDestination;
	AActor* CachedActor;
	bool isCachedActorInteractible;
	bool clickedOnWall;
	bool DoubleClicked = false;
	float FollowTime; // For how long it has been pressed
};
