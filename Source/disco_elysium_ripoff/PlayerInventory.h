// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "InventoryEntry.h"

#include "UObject/NoExportTypes.h"
#include "PlayerInventory.generated.h"
/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API UPlayerInventory : public UObject
{
	GENERATED_BODY()
public:

	UPlayerInventory();

	UFUNCTION()
	void AddItemToInventory(const FName& name, UInventoryEntry* entry);

	UFUNCTION()
	bool HasItem(const FName& name);

private:
	TMap<FName, UInventoryEntry*> Inventory;
	
};
