// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryListView.h"
#include "InventoryEntry.h"
#include "InventoryUIEntry.h"
#include "../MainGameInstanceSubsystem.h"

void UInventoryListView::NativeConstruct()
{
	Super::NativeConstruct();

	// Imagine we have an inventory class that provides us with the following:
}

void UInventoryListView::OnInventotyEntryAdded(UInventoryEntry* entry) {
	InventoryListView->AddItem(entry);
}