// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "DERSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API UDERSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category= Basic)
	TSet<FName> InventoryEntries; //TODO: here and everywhere -- this really should be FString to save time on all conversions, right? At least anywhere that is not UI

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;

	UDERSaveGame();
	
};
