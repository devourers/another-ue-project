// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "Components/SphereComponent.h"
#include "Interactable/LogicComponent.h"
#include "../MainGameInstanceSubsystem.h"

#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DISCO_ELYSIUM_RIPOFF_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION()
	virtual void ToggleHighlight(bool to_toggle) = 0;

	UFUNCTION()
	virtual void OnDialogueEnded(int LastEntryValue);

	UFUNCTION()
	virtual void ProcessDialogue();

	UFUNCTION()
	virtual void ProcessInventoryEntry();

	UFUNCTION()
	virtual void ProcessLoreEntry();

	UFUNCTION()
	virtual void ProcessNoteEntry();

	UFUNCTION()
	virtual void Interact(AActor* other_actor);

	UFUNCTION()
	virtual void InternalInteract(AActor* other_actor) = 0;

	UFUNCTION()
	virtual void OnCursorOver(UPrimitiveComponent* Component) = 0;

	UFUNCTION()
	virtual void OnCursorEnd(UPrimitiveComponent* Component) = 0;

	UFUNCTION()
	virtual void SetIsSelectedAsDestination(bool isSelected);

	UFUNCTION()
	virtual bool IsSelectedAsDestination();

	UFUNCTION()
	virtual void OnInteractableAsDestinationReached(AActor* other_actor) = 0;

	UFUNCTION()
	virtual void OnInteractableSelectedAsDestination() = 0;

	UFUNCTION()
	virtual USphereComponent* GetInteractionHitbox() = 0;

	UFUNCTION()
	virtual ULogicComponent* GetLogicComponent() = 0;

	UFUNCTION()
	virtual UMainGameInstanceSubsystem* GetHandler() = 0;

	UFUNCTION()
	virtual AProtagClass* GetProtag() = 0;

	UFUNCTION()
	virtual void BindProtag(AActor* other_actor) = 0;

protected:
	bool isSelectedAsDestination;
};
