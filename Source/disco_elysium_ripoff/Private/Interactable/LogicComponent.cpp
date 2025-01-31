// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/LogicComponent.h"

// Sets default values for this component's properties
ULogicComponent::ULogicComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


UDialogue* ULogicComponent::GetDialogue(){
	return Dialogue; 
}

ULoreEntry* ULogicComponent::GetLoreEntry(){
	return LoreEntry; 
}

UInventoryEntry* ULogicComponent::GetInventoryEntry(){
	return InventoryEntry; 
}

UNoteEntry* ULogicComponent::GetNoteEntry(){
	return NoteEntry; 
}

const FLogicOrder& ULogicComponent::GetLogicOrder() const
{
	return LogicOrder;
}


// Called when the game starts
void ULogicComponent::BeginPlay()
{
	Super::BeginPlay();

	if (LoaderName.IsEmpty())
		return;

	FString RootDir = FPaths::Combine(FPaths::ProjectContentDir(), *FString("Configs/Levels"));

	LoreEntryPath = FPaths::Combine(RootDir, GetWorld()->GetFName().ToString() + "/Lore/" + LoaderName + ".json");
	InventoryEntryPath = FPaths::Combine(RootDir, GetWorld()->GetFName().ToString() + "/Inventory/" + LoaderName + ".json");
	NoteEntryPath = FPaths::Combine(RootDir, GetWorld()->GetFName().ToString() + "/Notes/" + LoaderName + ".json");
	DialoguePath = FPaths::Combine(RootDir, GetWorld()->GetFName().ToString() + "/Dialogue/" + LoaderName + ".json");

	if (FPaths::FileExists(LoreEntryPath)) {
		LoreEntry = NewObject<ULoreEntry>(this, TEXT("Lore Entry"));
		LoreEntry->LoadFromJson(LoreEntryPath);
	}

	if (FPaths::FileExists(InventoryEntryPath)) {
		InventoryEntry = NewObject<UInventoryEntry>(this, TEXT("Inventory Entry"));
		InventoryEntry->LoadFromJson(InventoryEntryPath);
	}

	if (FPaths::FileExists(DialoguePath)) {
		Dialogue = NewObject<UDialogue>(this, TEXT("Dialogue"));
		Dialogue->LoadFromJson(DialoguePath);
	}

	if (FPaths::FileExists(NoteEntryPath)) {
		NoteEntry = NewObject<UNoteEntry>(this, TEXT("Note"));
		NoteEntry->LoadFromJson(NoteEntryPath);
	}
	
}


// Called every frame
void ULogicComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

