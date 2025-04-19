// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "DERSaveGame.generated.h"


USTRUCT()
struct FInteractableSaveData {
	GENERATED_BODY()

public:

	UPROPERTY()
	FName InteractableName;

	UPROPERTY()
	FTransform InteractableTransform; //for AI chars

	UPROPERTY()
	FString InteractableSubClass;

	UPROPERTY()
	TArray<uint8> ByteData;
};


USTRUCT()
struct FProtagSaveData {
	GENERATED_BODY()

public:

	FTransform ProtagTransform;

	UPROPERTY()
	TSet<FName> InventoryEntries; //TODO: here and everywhere -- this really should be FString to save time on all conversions, right? At least anywhere that is not UI

	UPROPERTY()
	TSet<FName> LoreEntries;

	UPROPERTY()
	TSet<FName> NoteEntries;

};
/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API UDERSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FString LevelName; //TODO -- make a pair from this and TMap? or no reason to?

	UPROPERTY()
	TMap<FName, FInteractableSaveData> InteractableSaveData;

	UPROPERTY()
	FProtagSaveData ProtagSaveData;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;

	UDERSaveGame();
	
};
