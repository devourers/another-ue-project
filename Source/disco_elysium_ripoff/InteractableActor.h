// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableActor.generated.h"

UCLASS()
class DISCO_ELYSIUM_RIPOFF_API AInteractableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

UFUNCTION()
	virtual FString GetName();

UFUNCTION()
	virtual FString GetDescription();

UFUNCTION()
	virtual void OnCursorOver(UPrimitiveComponent* Component);

UFUNCTION()
	void SetIsSelectedAsDestination(bool isSelected);

UFUNCTION()
	bool IsSelectedAsDestination();

UFUNCTION()
	virtual void OnCursorEnd(UPrimitiveComponent* Component);

UFUNCTION()
	virtual void OnActorSelectedAsDestination();

UFUNCTION()
	virtual void OnActorAsDestinationReached(AActor* other_actor);

private:
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = General, meta = (AllowPrivateAccess = "true"))
	FString Name;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = General, meta = (AllowPrivateAccess = "true"))
	FString Description;

private:
	bool isSelectedAsDestination;
};
