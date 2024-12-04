// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventory.h"

UPlayerInventory::UPlayerInventory() 
	:Super() 
{
	Inventory.Empty(1);
}

void UPlayerInventory::AddItemToInventory(const FName& name, UInventoryEntry* entry) {
	Inventory.Add({ name, entry });
	OnInventoryItemAdded.Broadcast(entry);
}

bool UPlayerInventory::HasItem(const FName& name) {
	return Inventory.Find(name) != nullptr;
}

TArray<UInventoryEntry*> UPlayerInventory::GetAllItems() {
	TArray<UInventoryEntry*> res;
	for (auto pair : Inventory) {
		res.Add(pair.Value);
	}
	return res;
}