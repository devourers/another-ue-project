// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Companion.h"
#include "AI/CompanionAIController.h"
#include "../PointAndClickPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACompanion::ACompanion()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	else
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}