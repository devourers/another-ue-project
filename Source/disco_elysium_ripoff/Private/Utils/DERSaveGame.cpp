// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/DERSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "../../MainGameInstanceSubsystem.h"

UDERSaveGame::UDERSaveGame(){
	SaveSlotName = TEXT("TestSaveSlot");
	UGameInstance* GI = UGameplayStatics::GetGameInstance(GetWorld());
	if (GI) {
		UMainGameInstanceSubsystem* handler = GI->GetSubsystem<UMainGameInstanceSubsystem>();
		if (handler) {
			InventoryEntries = handler->GetInventory()->GetAllItemsNames();
		}
	}
}
