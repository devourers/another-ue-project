// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/DialogueResponseListView.h"
#include "Components/ListView.h"

void UDialogueResponseListView::OnResponseAdded(UDialogueResponseWrapper* response){
	DialogueResponseListView->AddItem(response);
}

void UDialogueResponseListView::NativeConstruct(){
	Super::NativeConstruct();
}
