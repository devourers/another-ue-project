// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerActor.h"
#include "../ProtagClass.h"

// Sets default values
ATriggerActor::ATriggerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATriggerActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (TriggerVolume) {
		TriggerVolume->OnActorBeginOverlap.AddUniqueDynamic(this, &ATriggerActor::BroadcastBeginTrigger);
		TriggerVolume->OnActorEndOverlap.AddUniqueDynamic(this, &ATriggerActor::BroadcastEndTrigger);
	}
}

// Called every frame
void ATriggerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<class AActor*> ATriggerActor::GetConnectedActors() const {
	return ConnectedActors;
}

void ATriggerActor::BroadcastBeginTrigger(class AActor* ThisActor, AActor* OtherActor) {
	AProtagClass* protag = Cast<AProtagClass>(OtherActor);
	if (protag) {
		BeginOverlapTriggerDelegate.Broadcast();
	}
}

void ATriggerActor::BroadcastEndTrigger(class AActor* ThisActor, AActor* OtherActor) {
	AProtagClass* protag = Cast<AProtagClass>(OtherActor);
	if (protag) {
		EndOverlapTriggerDelegate.Broadcast();
	}
}
