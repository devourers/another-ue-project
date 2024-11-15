// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LoreEntry.generated.h"

/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API ULoreEntry : public UObject
{
	GENERATED_BODY()
	
	ULoreEntry() = default;

	void LoadFromJson();

private:
	FName Title; //displayed
	FName Subcategory;
	FName Caregory;
	
	TSet<FString> Keywords; //for searching
	FString JsonPath;

	TMap<FName, FString> Content; //header->name
	TMap<FName, UTexture2D*> ContentImages; //header->illustation
};
