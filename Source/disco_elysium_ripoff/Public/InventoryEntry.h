// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryEntry.generated.h"

/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API UInventoryEntry : public UObject
{
	GENERATED_BODY()

	UInventoryEntry() = default;

	void LoadFromJson();

private:
	FName Title; //displayed

	TSet<FString> Keywords; //for searching
	FString JsonPath;

	TMap<FName, FString> Description; //header->name
	TMap<FName, UTexture2D*> Image; //header->illustation
};
