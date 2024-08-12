// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventory.h"

UPlayerInventory::UPlayerInventory() 
	:Super() 
{
	Inventory.Empty(1);
}

void UPlayerInventory::AddItemToInventory(const FName& name, const FInventoryEntry& entry) {
	Inventory.Add({ name, entry });
}