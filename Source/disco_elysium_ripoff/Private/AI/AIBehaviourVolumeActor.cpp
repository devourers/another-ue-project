// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIBehaviourVolumeActor.h"
#include "../ProtagClass.h"

// Sets default values
AAIBehaviourVolumeActor::AAIBehaviourVolumeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAIBehaviourVolumeActor::BeginPlay()
{
	Super::BeginPlay();

	//fill by channel arrays
	for (int i = 0; i < ConnectedPOIs.Num(); ++i) {
		FString cur_channel = ConnectedPOIs[i]->GetChannel();
		if (!ConnectedPOIsByChannel.Contains(cur_channel)) {
			TArray<class AAIPointOfInterest*> cur_array;
			FPOIByChannel cur_struct;
			cur_struct.POIs = cur_array;
			cur_struct.Channel = cur_channel;
			cur_struct.POIs.Add(ConnectedPOIs[i]);
			ConnectedPOIsByChannel.Add(TTuple<FString, FPOIByChannel>(cur_channel, cur_struct));
		}
		else {
			ConnectedPOIsByChannel[cur_channel].POIs.Add(ConnectedPOIs[i]);
		}
	}

	if (AIPOIVolume) {
		AIPOIVolume->OnActorBeginOverlap.AddUniqueDynamic(this, &AAIBehaviourVolumeActor::BroadcastBeginTrigger);
		AIPOIVolume->OnActorEndOverlap.AddUniqueDynamic(this, &AAIBehaviourVolumeActor::BroadcastEndTrigger);
	}
	
}

// Called every frame
void AAIBehaviourVolumeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TSet<FString> AAIBehaviourVolumeActor::GetChannels() const{
	TSet<FString> res;
	ConnectedPOIsByChannel.GetKeys(res);
	return res;
}

TArray<class AAIPointOfInterest*> AAIBehaviourVolumeActor::GetConnectedPOIsByChannel(const FString& channel) const{
	if (ConnectedPOIsByChannel.Contains(channel)) {
		return ConnectedPOIsByChannel[channel].POIs;
	}
	else {
		return TArray<class AAIPointOfInterest*>();
	}
}

void AAIBehaviourVolumeActor::BroadcastBeginTrigger(class AActor* ThisActor, AActor* OtherActor) {
	AProtagClass* protag = Cast<AProtagClass>(OtherActor);
	if (protag) {
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString("In ABI volume"));
		BeginOverlapTriggerDelegate.Broadcast();
	}
}

void AAIBehaviourVolumeActor::BroadcastEndTrigger(class AActor* ThisActor, AActor* OtherActor) {
	AProtagClass* protag = Cast<AProtagClass>(OtherActor);
	if (protag) {
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString("Out of volume"));
		EndOverlapTriggerDelegate.Broadcast();
	}
}

