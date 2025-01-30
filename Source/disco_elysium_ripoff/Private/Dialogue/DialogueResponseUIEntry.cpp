// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/DialogueResponseUIEntry.h"

#include "Dialogue/Dialogue.h"
#include "Components/TextBlock.h"

void UDialogueResponseUIEntry::NativeOnListItemObjectSet(UObject* ListItemObject){
	UDialogueResponseWrapper* Response = Cast<UDialogueResponseWrapper>(ListItemObject);
	ResponseText->SetText(Response->response_.ResponseText);
}
