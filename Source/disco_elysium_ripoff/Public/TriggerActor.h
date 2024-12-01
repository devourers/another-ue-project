// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "TriggerActor.generated.h"

class ATriggerActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTriggerActorOverlapping);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTriggerActorEndOverlapping);

UCLASS()
class DISCO_ELYSIUM_RIPOFF_API ATriggerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	TArray<class AActor*> GetConnectedActors() const;

	UFUNCTION()
	void BroadcastBeginTrigger(class AActor* ThisActor, AActor* OtherActor);

	UFUNCTION()
	void BroadcastEndTrigger(class AActor* ThisActor, AActor* OtherActor);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Volume, meta = (AllowPrivateAccess = "true"))
	class ATriggerVolume* TriggerVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ConnectedActors, meta = (AllowPrivateAccess = "true"))
	TArray<class AActor*> ConnectedActors;

	UPROPERTY(BlueprintAssignable, Category = Event)
	FTriggerActorOverlapping BeginOverlapTriggerDelegate;

	UPROPERTY(BlueprintAssignable, Category = Event)
	FTriggerActorEndOverlapping EndOverlapTriggerDelegate;
};
