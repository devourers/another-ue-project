// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Json.h"
#include "InventoryEntry.generated.h"

/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API UInventoryEntry : public UObject
{
	GENERATED_BODY()

public:
	UInventoryEntry() = default;
	UInventoryEntry(UInventoryEntry* other);

	void LoadFromJson(const FString& path);

	FName GetTitle() { return Title; }
	TSet<FString> GetKeywords() { return Keywords; }
	FString GetDescription() { return Description; }
	TMap<FName, UTexture2D*> GetImages() { return Image; }

	void SetTitle(FName title) { Title = title; }
	void SetKeywords(TSet<FString> keywords) { Keywords = keywords; }
	void SetDescription(FString description) { Description = description; }
	void SetImages(TMap<FName, UTexture2D*> images) { Image = images; }

	bool IsValid() const;

private:
	bool is_initialised = false;
	bool is_valid = true;

	FName Title; //displayed

	TSet<FString> Keywords; //for searching
	FString JsonPath;

	FString Description; //header->name
	TMap<FName, UTexture2D*> Image; //header->illustation
};
