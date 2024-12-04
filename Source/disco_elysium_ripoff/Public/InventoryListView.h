// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryListView.generated.h"

/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API UInventoryListView : public UUserWidget
{
	GENERATED_BODY()

UFUNCTION()
	void OnInventotyEntryAdded(UInventoryEntry* entry);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UListView* InventoryListView;
};
