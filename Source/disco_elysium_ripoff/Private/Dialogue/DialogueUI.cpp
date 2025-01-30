// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/DialogueUI.h"

#include "Components/ListView.h"
#include "Components/TextBlock.h"

void UDialogueUI::NativeConstruct(){
	Super::NativeConstruct();
	ResponsesListView->OnItemSelectionChanged().AddUFunction(this, FName("OnResponseSelectionChanged"));
}

FReply UDialogueUI::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	return FReply::Handled();
}

void UDialogueUI::LogConversation(){

}

void UDialogueUI::BindDialogue(UDialogue* dialogue){
	dialogue_ = dialogue;
	dialogue_->DialogueStarted.AddUniqueDynamic(this, &UDialogueUI::OnDialogueStarted);
	dialogue_->DialogueAdvanced.AddUniqueDynamic(this, &UDialogueUI::OnDialogueAdvanced);
	dialogue_->DialogueEnded.AddUniqueDynamic(this, &UDialogueUI::OnDialogueEnded);
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
	RemoveFromViewport(); //move to instigator call
}