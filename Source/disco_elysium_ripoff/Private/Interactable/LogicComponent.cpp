// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/LogicComponent.h"
#include "../PointAndClickPlayerController.h"
#include "Dialogue/DialogueUI.h"

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

ELogicOrder ULogicComponent::GetLogicOrder() const {
	return LogicOrder;
}

const FString& ULogicComponent::GetLoaderName() const {
	return LoaderName;
}

const FString& ULogicComponent::GetWorldName() const
{
	return WorldName;
}

const FString& ULogicComponent::GetDisplayedName() const
{
	return DisplayedName;
}

UDialogueUI* ULogicComponent::CreateDialogueUI(APointAndClickPlayerController* PCC, AProtagClass* protag){
	if (Dialogue && !DialogueUI && DialogueUIClass) {
		DialogueUI = CreateWidget<UDialogueUI>(PCC, DialogueUIClass);
		DialogueUI->BindDialogue(Dialogue);
		DialogueUI->BindLogicComponent(this);
		DialogueUI->BindProtag(protag);
		Dialogue->StartDialogue();
		return DialogueUI;
	}
	else {
		return nullptr;
	}
}

void ULogicComponent::CloseDialogueUI() {
	DialogueUI->RemoveFromParent();
	DialogueUI = nullptr;
}


// Called when the game starts
void ULogicComponent::BeginPlay()
{
	Super::BeginPlay();

	WorldName = GetWorld()->GetName();

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

