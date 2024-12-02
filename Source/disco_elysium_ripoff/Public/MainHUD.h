// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API UMainHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	void AddLogEntry(const FString& log_entry);

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UScrollBox* LogScroll;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* Log;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* InventoryButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* LoreButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* NotesButton;
};
