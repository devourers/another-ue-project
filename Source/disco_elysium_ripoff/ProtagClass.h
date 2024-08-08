// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* ProtagCameraComponent;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* ProtagMeshComponent;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPathFollowingComponent* PathFinderComponent;

UFUNCTION()
	void CustomMoveToLocation(const FVector& target_location);

	//glossary
	//inventory
	

};
