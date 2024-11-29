// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "LevelChanger.generated.h"

UCLASS()
class DISCO_ELYSIUM_RIPOFF_API ALevelChanger : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelChanger();

	virtual void ToggleHighlight(bool to_toggle) override;

	virtual void Interact(AActor* other_actor) override;

	virtual void OnCursorOver(UPrimitiveComponent* Component) override;

	virtual void OnCursorEnd(UPrimitiveComponent* Component) override;

	virtual void OnInteractableAsDestinationReached(AActor* other_actor) override;

	virtual void OnInteractableSelectedAsDestination() override;

	virtual USphereComponent* GetInteractionHitbox() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
