// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/CanvasPanel.h"
#include "MainHUD.generated.h"


UENUM()
enum EActiveWidget {
	eAW_Hidden = 0,
	eAW_Inventory = 1,
	eAW_Lore = 2,
	eAW_Notes = 3
};

/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API UMainHUD : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	void AddLogEntry(const FString& log_entry);

protected:
	UFUNCTION()
	void OnInventoryButtonClicked();

	UFUNCTION()
	void OnLoreButtonClicked();

	UFUNCTION()
	void OnNotesButtonClicked();

	UFUNCTION()
	void OnInventotyEntryAdded(UInventoryEntry* entry);

	UFUNCTION()
	void OnInventotyEntrySelected(UObject* SelectedObject);

	UFUNCTION()
	void UpdateInventoryDetailsScreen(UInventoryEntry* entry);

protected:

	//LOG
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UScrollBox* LogScroll;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* Log;

	//TABS
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UWidgetSwitcher* EntryTabs;

	//INVENTORY
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* InventoryButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* InventoryPanel;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UListView* InventoryListView;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* InventoryListEntryTitle;

	//LORE
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* LoreButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* LorePanel;

	//NOTES
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* NotesButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* NotesPanel;

private:
	TEnumAsByte<EActiveWidget> ActiveWidget;
	

};
