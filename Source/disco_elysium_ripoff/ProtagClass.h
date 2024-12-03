// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "NavigationSystem.h"
#include "MainHUD.h"
#include "Public/Interactable.h"
#include "Public/ProtagOcclusionHandler.h"
#include "Components/BoxComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "ProtagClass.generated.h"

UCLASS()
class DISCO_ELYSIUM_RIPOFF_API AProtagClass : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AProtagClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void UpdateLog(const FString& log_entry);

UFUNCTION()
	void CameraBoomCollisionBegin(
		class UPrimitiveComponent* HitComp,
		class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult);

UFUNCTION()
	void CameraBoomCollisionEnd(
		class UPrimitiveComponent* HitComp, 
		class AActor* OtherActor, 
		class UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex);

UFUNCTION()
	void CustomMoveToInteractable(AActor* actor);

UFUNCTION()
	void CustomMoveToLocation(const FVector& target_location);

UFUNCTION()
	void StopPathfinderMovement();

UFUNCTION()
	void OnReachedPathDestinaton();

UFUNCTION()
	void FadeCamera(bool FadeIn);

UFUNCTION()
	void FadeOutAfterTeleport();

UFUNCTION()
	bool IsBehindWall() const;

private:
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* ProtagCameraComponent;

UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pathfinding, meta = (AllowPrivateAccess = "true"))
	UPathFollowingComponent* PathFinderComponent;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pathfinding, meta = (AllowPrivateAccess = "true"))
	UNavigationSystemV1* NavSystem;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CameraCollision, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* SpringArmCollisionVolume;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CameraCollision, meta = (AllowPrivateAccess = "true"))
	UProtagOcclusionHandler* OcclusionHandler;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FX, meta = (AllowPrivateAccess = "true"))
	class UNiagaraSystem* MoveToEffect;

UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainHUD> ProtagHUDClass;

UPROPERTY()
	class UMainHUD* ProtagHUD;

private:
	bool isMovingAlongPath = false;
	IInteractable* cached_actor = nullptr;
	bool isBehindWall;




	//glossary
	//inventory
	

};
