// Fill out your copyright notice in the Description page of Project Settings.


#include "ProtagClass.h"

// Sets default values
AProtagClass::AProtagClass()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProtagCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("ProtagCamera"));
	check(ProtagCameraComponent != nullptr);
	ProtagCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
	ProtagCameraComponent->SetRelativeLocation(FVector(10.0f, 10.0f, 10.0f));
	
	ProtagMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	check(ProtagMeshComponent != nullptr);

	PathFinderComponent = CreateDefaultSubobject<UPathFollowingComponent>(TEXT("Pathfinder"));
}

void AProtagClass::CustomMoveToLocation(const FVector& target_location) {
	FAIMoveRequest request;
	request.SetUsePathfinding(true);
	request.SetGoalLocation(target_location);
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

