// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "AIPointOfInterest.h"
#include "Engine/TriggerVolume.h"

#include "AIBehaviourVolumeActor.generated.h"

USTRUCT()
struct FPOIByChannel {
	GENERATED_BODY()

public:
	FString Channel;
	TArray<class AAIPointOfInterest*> POIs;
};

class AAIBehaviourVolumeActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAIVolumeOverlapping);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAIVolumeEndOverlapping);

UCLASS()
class DISCO_ELYSIUM_RIPOFF_API AAIBehaviourVolumeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIBehaviourVolumeActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	TSet<FString> GetChannels() const;

	UFUNCTION()
	TArray<class AAIPointOfInterest*> GetConnectedPOIsByChannel(const FString& channel) const;

	UFUNCTION()
	void BroadcastBeginTrigger(class AActor* ThisActor, AActor* OtherActor);

	UFUNCTION()
	void BroadcastEndTrigger(class AActor* ThisActor, AActor* OtherActor);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Volume, meta = (AllowPrivateAccess = "true"))
	class ATriggerVolume* AIPOIVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ConnectedActors, meta = (AllowPrivateAccess = "true"))
	TArray<class AAIPointOfInterest*> ConnectedPOIs;

	UPROPERTY()
	TMap<FString, FPOIByChannel> ConnectedPOIsByChannel;

	UPROPERTY(BlueprintAssignable, Category = Event)
	FAIVolumeOverlapping BeginOverlapTriggerDelegate;

	UPROPERTY(BlueprintAssignable, Category = Event)
	FAIVolumeEndOverlapping EndOverlapTriggerDelegate;

};
