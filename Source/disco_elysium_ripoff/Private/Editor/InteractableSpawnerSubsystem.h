// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Logging/StructuredLog.h"
#include "EditorSubsystem.h"
#include "InteractableSpawnerSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(InteractableSpawnerSubsystem, Log, All);

/**
 * 
 */
UCLASS()
class UInteractableSpawnerSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	UFUNCTION()
	void OnInteractableActorDropped(const TArray<UObject*>& DroppedObjects, const TArray<AActor*>& DroppedActors);

private:
	
};
