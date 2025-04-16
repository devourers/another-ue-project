// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUD.h"

#include "InventoryEntry.h"
#include "../MainGameInstanceSubsystem.h"
#include "../ProtagClass.h"
#include "Components/ListView.h"

void UMainHUD::NativeConstruct() {
	Super::NativeConstruct();
	EntryTabs->SetVisibility(ESlateVisibility::Hidden);
	InventoryButton->OnClicked.AddUniqueDynamic(this, &UMainHUD::OnInventoryButtonClicked);
	LoreButton->OnClicked.AddUniqueDynamic(this, &UMainHUD::OnLoreButtonClicked);
	NotesButton->OnClicked.AddUniqueDynamic(this, &UMainHUD::OnNotesButtonClicked);

	TArray<UInventoryEntry*> Inventory;

	UMainGameInstanceSubsystem* handler = GetOwningPlayerPawn()->GetGameInstance()->GetSubsystem<UMainGameInstanceSubsystem>();
	TArray<UInventoryEntry*> entries = handler->GetInventory()->GetAllItems();
	handler->GetInventory()->OnInventoryItemAdded.AddUniqueDynamic(this, &UMainHUD::OnInventotyEntryAdded);
	InventoryListView->SetVisibility(ESlateVisibility::Visible);
	InventoryListView->SetListItems(entries);
	InventoryListView->OnItemSelectionChanged().AddUFunction(this, FName("OnInventotyEntrySelected"));
}

FReply UMainHUD::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) {
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UMainHUD::AddLogEntry(const FString& log_entry) {
	if (Log) {
		FText log_text = Log->GetText();
		FText new_text = FText::FromString(log_text.ToString() + "\n" + log_entry);
		Log->SetText(new_text);
		LogScroll->ScrollToEnd();
	}
}

void UMainHUD::OnInventoryButtonClicked() {
	if (ActiveWidget != EActiveWidget::eAW_Inventory) {
		if (protag_)
			protag_->DisableProtagInput();
		ActiveWidget = EActiveWidget::eAW_Inventory;
		EntryTabs->SetVisibility(ESlateVisibility::Visible);
		EntryTabs->SetActiveWidget(InventoryPanel);
	}
	else {
		if (protag_)
			protag_->EnableProtagInput();
		ActiveWidget = EActiveWidget::eAW_Hidden;
		EntryTabs->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMainHUD::OnLoreButtonClicked() {
	if (ActiveWidget != EActiveWidget::eAW_Lore) {
		if (protag_)
			protag_->DisableProtagInput();
		ActiveWidget = EActiveWidget::eAW_Lore;
		EntryTabs->SetVisibility(ESlateVisibility::Visible);
		EntryTabs->SetActiveWidget(LorePanel);
	}
	else {
		if (protag_)
			protag_->EnableProtagInput();
		ActiveWidget = EActiveWidget::eAW_Hidden;
		EntryTabs->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMainHUD::OnNotesButtonClicked() {
	if (ActiveWidget != EActiveWidget::eAW_Notes) {
		if (protag_)
			protag_->DisableProtagInput();
		ActiveWidget = EActiveWidget::eAW_Notes;
		EntryTabs->SetVisibility(ESlateVisibility::Visible);
		EntryTabs->SetActiveWidget(NotesPanel);
	}
	else {
		if (protag_)
			protag_->EnableProtagInput();
		ActiveWidget = EActiveWidget::eAW_Hidden;
		EntryTabs->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMainHUD::OnInventotyEntryAdded(UInventoryEntry* entry) {
	InventoryListView->AddItem(entry);
}

void UMainHUD::OnInventotyEntrySelected(UObject* SelectedObject) {
	UInventoryEntry* entry = Cast<UInventoryEntry>(SelectedObject);
	if (entry) {
		UpdateInventoryDetailsScreen(entry);
	}
}

void UMainHUD::UpdateInventoryDetailsScreen(UInventoryEntry* entry) {
	InventoryListEntryTitle->SetText(FText::FromName(entry->GetTitle()));
	InventoryLineEntryDescription->SetText(FText::FromString(entry->GetDescription()));
}

void UMainHUD::BindProtag(AProtagClass* protag){
	protag_ = protag;
}
