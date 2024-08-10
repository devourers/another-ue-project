// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableActor.h"

// Sets default values
AInteractableActor::AInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AInteractableActor::GetName() {
	return Name;
}

FString AInteractableActor::GetDescription() {
	return Description;
}

void AInteractableActor::OnCursorOver(UPrimitiveComponent* Component) {

}


void AInteractableActor::OnCursorEnd(UPrimitiveComponent* Component) {

}


void AInteractableActor::OnActorSelectedAsDestination() {

}


void AInteractableActor::OnActorAsDestinationReached() {

}


void AInteractableActor::SetIsSelectedAsDestination(bool isSelected) {
	isSelectedAsDestination = isSelected;
}


bool AInteractableActor::IsSelectedAsDestination() {
	return isSelectedAsDestination;
}