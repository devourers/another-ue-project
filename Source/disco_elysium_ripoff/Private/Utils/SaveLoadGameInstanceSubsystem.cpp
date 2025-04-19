// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/SaveLoadGameInstanceSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "GameFramework/GameStateBase.h"
#include <Utils/DERSaveGame.h>
#include <Interactable.h>
#include <../ProtagClass.h>
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

DEFINE_LOG_CATEGORY(SaveLoadGameInstanceSubsystem);

void USaveLoadGameInstanceSubsystem::WriteSaveGame(FString SlotName){
	if (UDERSaveGame* SaveGameInstance = Cast<UDERSaveGame>(UGameplayStatics::CreateSaveGameObject(UDERSaveGame::StaticClass()))) {
		SaveGameInstance->SaveSlotName = "TestFromPause";
		for (AActor* Actor : TActorRange<AActor>(GetWorld())){
			if (!Actor->Implements<UInteractable>()) {
				continue;
			}
			UE_LOG(SaveLoadGameInstanceSubsystem, Log, TEXT("Actor %s"), *(Actor->GetName()));
			FInteractableSaveData InteractableSaveData;
			InteractableSaveData.InteractableTransform = Actor->GetActorTransform();
			InteractableSaveData.InteractableSubClass = Actor->StaticClass()->GetName();
			UE_LOG(SaveLoadGameInstanceSubsystem, Log, TEXT("Actor  Class %s"), *(InteractableSaveData.InteractableSubClass));
			SaveGameInstance->InteractableSaveData.Add(TTuple<FName, FInteractableSaveData>(Actor->GetFName(), InteractableSaveData));

			//TODO

		}

		AProtagClass* protag = Cast<AProtagClass>(GetWorld()->GetFirstPlayerController()->GetPawn());
		SaveGameInstance->ProtagSaveData.ProtagTransform = protag->GetTransform();
		
		FString SlotNameString = "TestFromPause";
		if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotNameString, 0)){
			UE_LOG(SaveLoadGameInstanceSubsystem, Log, TEXT("Protag Transform %s"), *SaveGameInstance->ProtagSaveData.ProtagTransform.ToString());
			UE_LOGFMT(SaveLoadGameInstanceSubsystem, Log, "Game Saved");
		}
		else {
			UE_LOGFMT(SaveLoadGameInstanceSubsystem, Log, "Game failed to save");
		}
	}
}

void USaveLoadGameInstanceSubsystem::LoadSaveGame(FString SlotName){
	if (UDERSaveGame* LoadedGame = Cast<UDERSaveGame>(UGameplayStatics::LoadGameFromSlot("TestFromPause", 0))) {
		UE_LOGFMT(SaveLoadGameInstanceSubsystem, Log, "Game loaded");
		
		AProtagClass* protag = Cast<AProtagClass>(GetWorld()->GetFirstPlayerController()->GetPawn());
		UE_LOG(SaveLoadGameInstanceSubsystem, Log, TEXT("Protag Transform %s"), *LoadedGame->ProtagSaveData.ProtagTransform.ToString());
		protag->SetActorTransform(LoadedGame->ProtagSaveData.ProtagTransform);

	}
}

void USaveLoadGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection){
	Super::Initialize(Collection);
	UE_LOGFMT(SaveLoadGameInstanceSubsystem, Log, "Initialised save subsystem");
}
