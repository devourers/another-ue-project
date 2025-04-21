// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstanceSubsystem.h"

DEFINE_LOG_CATEGORY(MainGameInstanceSubsystem);

void UMainGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);
	Inventory = NewObject<UPlayerInventory>(this, UPlayerInventory::StaticClass());
	UE_LOGFMT(MainGameInstanceSubsystem, Log, "Initialised main subsystem");
}


void UMainGameInstanceSubsystem::Deinitialize() {
	Super::Deinitialize();
	UE_LOGFMT(MainGameInstanceSubsystem, Log, "Deinitialised main subsystem");
}

void UMainGameInstanceSubsystem::AddItemToInventory(const FName& name, UInventoryEntry* item) {
	Inventory->AddItemToInventory(name, item); //internal function is more complex since it decides where to add it.
	UE_LOGFMT(MainGameInstanceSubsystem, Log, "Added item {0} to inventory", name);
}

bool UMainGameInstanceSubsystem::CheckInventoryForItem(const FName& name) {
	return Inventory->HasItem(name);
}

UPlayerInventory* UMainGameInstanceSubsystem::GetInventory() {
	return Inventory;
}

int UMainGameInstanceSubsystem::GetCurrentLevelPhase() const{
	return CurrentLevelPhase;
}

void UMainGameInstanceSubsystem::SetCurrentLevelPhase(int current_level_phase) {
	CurrentLevelPhase = current_level_phase;
}
