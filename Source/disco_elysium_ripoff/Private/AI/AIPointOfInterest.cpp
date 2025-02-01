// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIPointOfInterest.h"

// Sets default values
AAIPointOfInterest::AAIPointOfInterest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAIPointOfInterest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIPointOfInterest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

const FString& AAIPointOfInterest::GetChannel() const {
	return Channel;
}

const TArray<TEnumAsByte<EPOIAction>>& AAIPointOfInterest::GetAvaliableActions() const {
	return AvaliableActions;
}

