// Fill out your copyright notice in the Description page of Project Settings.


#include "LoreUIEntry.h"
#include "LoreEntry.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void ULoreUIEntry::NativeOnListItemObjectSet(UObject* ListItemObject) {
	ULoreEntry* Item = Cast<ULoreEntry>(ListItemObject);
	//TODO NameLabel->SetText(FText::FromString(Item->Get.ToString()));
	//IconImage->SetBrushFromTexture(Item->Icon);
}