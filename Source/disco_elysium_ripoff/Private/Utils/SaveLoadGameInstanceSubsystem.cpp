// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/SaveLoadGameInstanceSubsystem.h"

DEFINE_LOG_CATEGORY(SaveLoadGameInstanceSubsystem);

void USaveLoadGameInstanceSubsystem::WriteSaveGame(FString SlotName){
	UE_LOGFMT(SaveLoadGameInstanceSubsystem, Log, "Saving");
}

void USaveLoadGameInstanceSubsystem::LoadSaveGame(FString SlotName){
	UE_LOGFMT(SaveLoadGameInstanceSubsystem, Log, "Loading");
}

void USaveLoadGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection){
	Super::Initialize(Collection);
	UE_LOGFMT(SaveLoadGameInstanceSubsystem, Log, "Initialised save subsystem");
}
