// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryUIEntry.h"

#include "InventoryEntry.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UInventoryUIEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UInventoryEntry* Item = Cast<UInventoryEntry>(ListItemObject);
	NameLabel->SetText(FText::FromString(Item->GetTitle().ToString()));
	//IconImage->SetBrushFromTexture(Item->Icon);
}
