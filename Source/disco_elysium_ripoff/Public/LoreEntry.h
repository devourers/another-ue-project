// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Json.h"
#include "LoreEntry.generated.h"

/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API ULoreEntry : public UObject
{
	GENERATED_BODY()

public:
	ULoreEntry() = default;

	void LoadFromJson(const FString& path);

	bool IsValid() const;

private:
	bool is_valid = true;

	FName Title; //displayed
	FName Subcategory;
	FName Category;
	
	TSet<FString> Keywords; //for searching
	FString JsonPath;

	TMap<FName, FString> Content; //header->name
	TMap<FName, UTexture2D*> ContentImages; //header->illustation
};
