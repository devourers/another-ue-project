// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "InventoryEntry.h"

#include "Components/ListView.h"

#include "UObject/NoExportTypes.h"
#include "PlayerInventory.generated.h"
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryChanged, class UInventoryEntry*, Entry);

UCLASS()
class DISCO_ELYSIUM_RIPOFF_API UPlayerInventory : public UObject
{
	GENERATED_BODY()
public:

	UPlayerInventory();

	UFUNCTION()
	void ClearInventory();

	UFUNCTION()
	void AddItemToInventory(const FName& name, UInventoryEntry* entry);

	UFUNCTION()
	void RemoveItemFromInventory(const FName& name);

	UFUNCTION()
	bool HasItem(const FName& name);

	UFUNCTION()
	TArray<UInventoryEntry*> GetAllItems();

	UFUNCTION()
	TSet<FName> GetAllItemsNames();

	UPROPERTY(BlueprintAssignable)
	FInventoryChanged OnInventoryItemAdded;

	UPROPERTY(BlueprintAssignable)
	FInventoryChanged OnInventoryItemRemoved;

private:
	UPROPERTY()
	TMap<FName, UInventoryEntry*> Inventory;
	
};
