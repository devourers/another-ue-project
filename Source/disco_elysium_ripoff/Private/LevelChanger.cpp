// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelChanger.h"

// Sets default values
ALevelChanger::ALevelChanger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelChanger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelChanger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelChanger::ToggleHighlight(bool to_toggle) {

}

void ALevelChanger::Interact(AActor* other_actor) {

}

void ALevelChanger::OnCursorOver(UPrimitiveComponent* Component) {

}

void ALevelChanger::OnCursorEnd(UPrimitiveComponent* Component) {

}

void ALevelChanger::OnInteractableAsDestinationReached(AActor* other_actor) {

}

void ALevelChanger::OnInteractableSelectedAsDestination() {

}

USphereComponent* ALevelChanger::GetInteractionHitbox() {
	return nullptr;
}