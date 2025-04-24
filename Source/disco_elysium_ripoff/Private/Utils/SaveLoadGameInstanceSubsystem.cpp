// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/SaveLoadGameInstanceSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "GameFramework/GameStateBase.h"
#include <Utils/DERSaveGame.h>
#include <Interactable.h>
#include <../ProtagClass.h>
#include <Interactable/LogicComponent.h>
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

DEFINE_LOG_CATEGORY(SaveLoadGameInstanceSubsystem);

void USaveLoadGameInstanceSubsystem::WriteSaveGame(FString SlotName){
	UGameInstance* GI = UGameplayStatics::GetGameInstance(GetWorld());
	if (UDERSaveGame* SaveGameInstance = Cast<UDERSaveGame>(UGameplayStatics::CreateSaveGameObject(UDERSaveGame::StaticClass()))) {
		SaveGameInstance->LevelName = GetWorld()->GetName();
		SaveGameInstance->SaveSlotName = "TestFromPause";
		for (AActor* Actor : TActorRange<AActor>(GetWorld())){
			if (!Actor->Implements<UInteractable>()) {
				continue;
			}
			UE_LOG(SaveLoadGameInstanceSubsystem, Log, TEXT("Actor %s"), *(Actor->GetName()));
			FInteractableSaveData InteractableSaveData;
			InteractableSaveData.InteractableTransform = Actor->GetActorTransform();
			InteractableSaveData.InteractableSubClass = Actor->StaticClass()->GetName();
			UE_LOG(SaveLoadGameInstanceSubsystem, Log, TEXT("Actor  Class %s"), *(InteractableSaveData.InteractableSubClass)); //TODO


			FMemoryWriter MemWriter(InteractableSaveData.ByteData);
			FObjectAndNameAsStringProxyArchive Ar(MemWriter, true);
			Ar.ArIsSaveGame = true;
			Actor->Serialize(Ar);

			SaveGameInstance->InteractableSaveData.Add(TTuple<FName, FInteractableSaveData>(Actor->GetFName(), InteractableSaveData));
			//TODO

		}

		AProtagClass* protag = Cast<AProtagClass>(GetWorld()->GetFirstPlayerController()->GetPawn());
		SaveGameInstance->ProtagSaveData.ProtagTransform = protag->GetTransform();

		UMainGameInstanceSubsystem* handler = GI->GetSubsystem<UMainGameInstanceSubsystem>();
		if (handler) {
			SaveGameInstance->CurrentLevelPhase = handler->GetCurrentLevelPhase();
			SaveGameInstance->ProtagSaveData.InventoryEntries = handler->GetInventory()->GetAllItemsNames();
			for (auto& name : SaveGameInstance->ProtagSaveData.InventoryEntries) {
				UE_LOG(SaveLoadGameInstanceSubsystem, Log, TEXT("inventory entry %s"), *name.ToString());
			}
		}
		FString SlotNameString = "TestFromPause";
		if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotNameString, 0)){
			UE_LOGFMT(SaveLoadGameInstanceSubsystem, Log, "Game Saved on level {0}", SaveGameInstance->LevelName);
		}
		else {
			UE_LOGFMT(SaveLoadGameInstanceSubsystem, Log, "Game failed to save");
		}
	}
}

void USaveLoadGameInstanceSubsystem::LoadSaveGame(FString SlotName){
	UGameInstance* GI = UGameplayStatics::GetGameInstance(GetWorld());
	if (UDERSaveGame* LoadedGame = Cast<UDERSaveGame>(UGameplayStatics::LoadGameFromSlot("TestFromPause", 0))) {
		UMainGameInstanceSubsystem* handler = GI->GetSubsystem<UMainGameInstanceSubsystem>();
		handler->GetInventory()->ClearInventory();
		UGameplayStatics::OpenLevel(GetWorld(), FName(LoadedGame->LevelName));
		AProtagClass* protag = Cast<AProtagClass>(GetWorld()->GetFirstPlayerController()->GetPawn());

		protag->SetActorTransform(LoadedGame->ProtagSaveData.ProtagTransform);
		for (auto& name : LoadedGame->ProtagSaveData.InventoryEntries) {
			TArray<FString> splitted_name;
			name.ToString().ParseIntoArray(splitted_name, TEXT("|"));
			FString level_name = splitted_name[0];
			FString interactable_name = splitted_name[1];
			FString root_dir = FPaths::Combine(FPaths::ProjectContentDir(), *FString("Configs/Levels"));
			FString inventory_entry_path = FPaths::Combine(root_dir, GetWorld()->GetFName().ToString() + "/Inventory/" + interactable_name + ".json");
			UInventoryEntry* InventoryEntry = NewObject<UInventoryEntry>(this, TEXT("Inventory Entry"));
			InventoryEntry->LoadFromJson(inventory_entry_path);
			
			handler->AddItemToInventory(name, InventoryEntry);
			UE_LOG(SaveLoadGameInstanceSubsystem, Log, TEXT("inventory entry %s"), *(name.ToString()));
		}
		UE_LOGFMT(SaveLoadGameInstanceSubsystem, Log, "Game loaded");
		LastLoadedSave = LoadedGame;
	}
}

void USaveLoadGameInstanceSubsystem::FinishSaveLoading() const{
	if (LastLoadedSave) {
		UGameInstance* GI = UGameplayStatics::GetGameInstance(GetWorld());
		TArray<AActor*> actors;
		UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UInteractable::StaticClass(), actors);
		for (auto actor : actors) {
			if (LastLoadedSave->InteractableSaveData.Contains(FName(actor->GetName()))) {
				UE_LOG(SaveLoadGameInstanceSubsystem, Log, TEXT("Actor present %s"), *actor->GetName());
				FInteractableSaveData* FoundData = LastLoadedSave->InteractableSaveData.Find(FName(actor->GetName()));
				FMemoryReader MemReader(FoundData->ByteData);

				FObjectAndNameAsStringProxyArchive Ar(MemReader, true);
				Ar.ArIsSaveGame = true;
				// Convert binary array back into actor's variables
				actor->Serialize(Ar);

				//IRogueGameplayInterface::Execute_OnActorLoaded(Actor);
			}
			else {
				bool actor_destroyed = actor->Destroy();
				FString res = "";
				if (actor_destroyed)
					res = "true";
				else
					res = "false";
				UE_LOG(SaveLoadGameInstanceSubsystem, Log, TEXT("Actor %s not present, destroy = %s"), *actor->GetName(), *res);
			}
		}
		UMainGameInstanceSubsystem* handler = GI->GetSubsystem<UMainGameInstanceSubsystem>();
		handler->SetCurrentLevelPhase(LastLoadedSave->CurrentLevelPhase);
	}
}

void USaveLoadGameInstanceSubsystem::PostBeginPlay() const {
	if (LastLoadedSave) {
		AProtagClass* protag = Cast<AProtagClass>(GetWorld()->GetFirstPlayerController()->GetPawn());
		protag->SetActorTransform(LastLoadedSave->ProtagSaveData.ProtagTransform);
	}
}

void USaveLoadGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection){
	Super::Initialize(Collection);
	UE_LOGFMT(SaveLoadGameInstanceSubsystem, Log, "Initialised save subsystem");
}
