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

	UFUNCTION()
	void AddItemToInventory(const FName& name, UInventoryEntry* item);

	UFUNCTION()
	bool CheckInventoryForItem(const FName& name);

	UFUNCTION()
	UPlayerInventory* GetInventory();

	UFUNCTION(BlueprintCallable)
	int GetCurrentLevelPhase() const;

	UFUNCTION(BlueprintCallable)
	void SetCurrentLevelPhase(int current_level_phase);

private:
	UPROPERTY()
	UPlayerInventory* Inventory;
	
	UPROPERTY()
	int CurrentLevelPhase = 0;

};
