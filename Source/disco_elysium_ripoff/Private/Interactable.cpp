// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"

// Add default functionality here for any IInteractable functions that are not pure virtual.


void IInteractable::Interact(AActor* other_actor){
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString("Interface called"));
	if (GetLogicComponent()) {
		const FLogicOrder& order = GetLogicComponent()->GetLogicOrder();
		if (order.Order.Num()) {
			for (auto entry : order.Order) {
				if (entry == ELogicType::eLT_Dialogue) {

				}
				else if (entry == ELogicType::eLT_Inventory) {

				}
				else if (entry == ELogicType::eLT_Lore) {

				}
				else if (entry == ELogicType::eLT_Note) {

				}
			}
		}
		else {
			//default behaivour
			//dialogue->if dialogue success note -> inventory -> lore
		}
	}
}

void IInteractable::SetIsSelectedAsDestination(bool isSelected) {
	isSelectedAsDestination = isSelected;
}


bool IInteractable::IsSelectedAsDestination() {
	return isSelectedAsDestination;
}