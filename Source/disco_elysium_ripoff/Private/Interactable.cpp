// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"
#include "../ProtagClass.h"
#include "Dialogue/DialogueUI.h"
#include "../PointAndClickPlayerController.h"

#include "Kismet/GameplayStatics.h"

// Add default functionality here for any IInteractable functions that are not pure virtual.

void IInteractable::OnDialogueEnded(int LastEntryValue) {
	ULogicComponent* logic = GetLogicComponent();
	const FDialogueResult& result = logic->GetDialogue()->GetResult();
	if (result.IsSuccessful) {
		ProcessInventoryEntry();
		ProcessNoteEntry();
		ProcessLoreEntry();
		InternalInteract(GetProtag());
	}
}


void IInteractable::ProcessDialogue() {
	AProtagClass* protag = GetProtag();
	ULogicComponent* logic = GetLogicComponent();
	if (protag && logic) {
		APointAndClickPlayerController* PCC = protag->GetController<APointAndClickPlayerController>();
		UDialogueUI* dialogue_ui = logic->CreateDialogueUI(PCC, protag);
		if (dialogue_ui) {
			logic->GetDialogue()->DialogueEnded.AddUniqueDynamic(this, &IInteractable::OnDialogueEnded);
			protag->InitDialogueWindow(dialogue_ui);
		}
	}
}

void IInteractable::ProcessInventoryEntry() {
	UMainGameInstanceSubsystem* handler = GetHandler();
	ULogicComponent* logic = GetLogicComponent();
	AProtagClass* protag = GetProtag();
	if (handler && logic) {
		UInventoryEntry* logic_entry = GetLogicComponent()->GetInventoryEntry();
		if (logic_entry) {
			UInventoryEntry* entry = NewObject<UInventoryEntry>();
			entry->SetTitle(logic_entry->GetTitle());
			entry->SetKeywords(logic_entry->GetKeywords());
			entry->SetDescription(logic_entry->GetDescription());
			entry->SetImages(logic_entry->GetImages());
			FName entry_name = FName(logic->GetWorldName() + "|" + logic->GetLoaderName());
			handler->AddItemToInventory(entry_name, entry);
			if (protag) {
				FString log_entry = FString("Item picked up: ") + logic->GetDisplayedName();
				protag->UpdateLog(log_entry);
			}
		}
	}
}

void IInteractable::ProcessLoreEntry() {
	UMainGameInstanceSubsystem* handler = GetHandler();
	ULogicComponent* logic = GetLogicComponent();
}

void IInteractable::ProcessNoteEntry() {
	UMainGameInstanceSubsystem* handler = GetHandler();
	ULogicComponent* logic = GetLogicComponent();
}

void IInteractable::Interact(AActor* other_actor){
	if (!GetInteractionHitbox()->IsOverlappingActor(other_actor))
		return;
	ULogicComponent* logic = GetLogicComponent();
	if (!GetProtag())
		BindProtag(other_actor);
	if (logic) {
		ELogicOrder order = logic->GetLogicOrder();
		if (order == ELogicOrder::eLO_DiagloueFirst) {
			ProcessDialogue();
		}
		else {
			ProcessInventoryEntry();
			ProcessNoteEntry();
			ProcessLoreEntry();
			InternalInteract(other_actor);
		}
	}

}

void IInteractable::SetIsSelectedAsDestination(bool isSelected) {
	isSelectedAsDestination = isSelected;
}


bool IInteractable::IsSelectedAsDestination() {
	return isSelectedAsDestination;
}