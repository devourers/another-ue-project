// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerInventory.generated.h"

USTRUCT(BlueprintType)
struct FInventoryEntry : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Thumbnail;

};

/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API UPlayerInventory : public UObject
{
	GENERATED_BODY()
public:

	UPlayerInventory();

	UFUNCTION()
	void AddItemToInventory(const FName& name, const FInventoryEntry& entry);

private:
	TMap<FName, FInventoryEntry> Inventory;
	
};
