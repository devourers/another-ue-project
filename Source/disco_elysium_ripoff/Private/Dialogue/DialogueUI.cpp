// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/DialogueUI.h"

#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "../../ProtagClass.h"

void UDialogueUI::NativeConstruct(){
	Super::NativeConstruct();
	ResponsesListView->OnItemSelectionChanged().AddUFunction(this, FName("OnResponseSelectionChanged"));
}

FReply UDialogueUI::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	return FReply::Handled();
}

void UDialogueUI::LogConversation(){
	const FDialogueHistory& history = dialogue_->GetHistory();
	FString dialogue_log;
	int history_size = history.entries.Num();
	for (int i = 0; i < history_size; ++i) {
		UDialogueEntryWrapper* cur_entry = dialogue_->GetEntry(history.entries[i]);
		dialogue_log += cur_entry->entry_.EntryCharacter.ToString() + FString(": ") + cur_entry->entry_.EntryText.ToString() + FString("\n");
		UDialogueResponseWrapper* cur_response = dialogue_->GetResponse(history.responses[i]);
		dialogue_log += FString("Player: ") + cur_response->response_.ResponseText.ToString() + FString("\n");
	}
	dialogue_log += FString("Conversation ended.");
	if (protag_) {
		protag_->UpdateLog(dialogue_log);
	}
}

void UDialogueUI::BindDialogue(UDialogue* dialogue){
	dialogue_ = dialogue;
	dialogue_->DialogueStarted.AddUniqueDynamic(this, &UDialogueUI::OnDialogueStarted);
	dialogue_->DialogueAdvanced.AddUniqueDynamic(this, &UDialogueUI::OnDialogueAdvanced);
	dialogue_->DialogueEnded.AddUniqueDynamic(this, &UDialogueUI::OnDialogueEnded);
}

void UDialogueUI::BindLogicComponent(ULogicComponent* logic){
	logic_ = logic;
}

void UDialogueUI::BindProtag(AProtagClass* protag){
	protag_ = protag;
}

void UDialogueUI::OnResponseSelectionChanged(UObject* SelectedObject){
	UDialogueResponseWrapper* response = Cast<UDialogueResponseWrapper>(SelectedObject);
	if (response) {
		dialogue_->AdvanceDialogue(response->response_.Id);
	}
}

void UDialogueUI::OnDialogueStarted(UDialogueEntryWrapper* entry) {
	CharacterName->SetText(FText::FromName(entry->entry_.EntryCharacter));
	EntryTextBlock->SetText(entry->entry_.EntryText);
	for (int response_id : entry->entry_.Responses) {
		UDialogueResponseWrapper* response = dialogue_->GetResponse(response_id);
		ResponsesListView->AddItem(response);
	}
}

void UDialogueUI::OnDialogueAdvanced(UDialogueEntryWrapper* entry) {
	CharacterName->SetText(FText::FromName(entry->entry_.EntryCharacter));
	EntryTextBlock->SetText(entry->entry_.EntryText);
	ResponsesListView->ClearListItems();
	for (int response_id : entry->entry_.Responses) {
		UDialogueResponseWrapper* response = dialogue_->GetResponse(response_id);
		ResponsesListView->AddItem(response);
	}
}

void UDialogueUI::OnDialogueEnded() {
	LogConversation();
	if (logic_) {
		logic_->CloseDialogueUI();
	}
}