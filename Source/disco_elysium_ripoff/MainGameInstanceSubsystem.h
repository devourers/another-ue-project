// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Logging/StructuredLog.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PlayerInventory.h"
#include "MainGameInstanceSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(MainGameInstanceSubsystem, Log, All);

/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API UMainGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void AddItemToInventory(const FName& name, UInventoryEntry* item);

	bool CheckInventoryForItem(const FName& name);

private:
	UPROPERTY()
	UPlayerInventory* Inventory;
	
};
