// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventory.h"

UPlayerInventory::UPlayerInventory() 
	:Super() 
{
	Inventory.Empty(1);
}

void UPlayerInventory::ClearInventory(){
	for (auto& item : Inventory) {
		OnInventoryItemRemoved.Broadcast(item.Value);
	}
	Inventory.Empty();
}

void UPlayerInventory::RemoveItemFromInventory(const FName& name) {
	if (Inventory.Contains(name)) {
		OnInventoryItemRemoved.Broadcast(Inventory[name]);
		Inventory.Remove(name);
	}

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

TSet<FName> UPlayerInventory::GetAllItemsNames() {
	TSet<FName> res;
	Inventory.GetKeys(res);
	return res;
}