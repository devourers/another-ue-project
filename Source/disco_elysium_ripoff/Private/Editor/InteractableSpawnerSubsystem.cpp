// Fill out your copyright notice in the Description page of Project Settings.


#include "Editor/InteractableSpawnerSubsystem.h"
#include "EditorUtilitySubsystem.h"
#include "PythonEditorHelper.h"
#include "EditorAssetLibrary.h"
#include "EngineUtils.h"
#include "EditorUtilitySubsystem.h"
#include "../../Public/Interactable.h"
#include "Subsystems/EditorActorSubsystem.h"
#include "LevelEditorSubsystem.h"

DEFINE_LOG_CATEGORY(InteractableSpawnerSubsystem);

FString ParseFileName(const FString& filename) {
	TArray<FString> Out;
	filename.ParseIntoArray(Out, TEXT("/"), true);
	if (Out.Num() > 0) {
		FString level_with_umap = Out[Out.Num() - 1];
		TArray<FString> Out_pt;
		level_with_umap.ParseIntoArray(Out_pt, TEXT(".umap"), true);
		if (Out_pt.Num() > 0)
			return Out_pt[0];
		else
			return FString();
	}
	else
		return FString();
}

void UInteractableSpawnerSubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Collection.InitializeDependency(UEditorActorSubsystem::StaticClass());
	Collection.InitializeDependency(ULevelEditorSubsystem::StaticClass());

	UE_LOGFMT(InteractableSpawnerSubsystem, Log, "Initialised interactable spawner subsystem");

	UEditorActorSubsystem* editor_actor_subsystem = GEditor->GetEditorSubsystem<UEditorActorSubsystem>();
	editor_actor_subsystem->OnNewActorsDropped.AddUniqueDynamic(this, &UInteractableSpawnerSubsystem::OnInteractableActorDropped);

	ULevelEditorSubsystem* level_editor_subsystem = GEditor->GetEditorSubsystem<ULevelEditorSubsystem>();
	level_editor_subsystem->OnMapOpened.AddUniqueDynamic(this, &UInteractableSpawnerSubsystem::OnMapOpened);

	LevelIndex = NewObject<ULevelIndex>(this, ULevelIndex::StaticClass());
	ActorIndex = NewObject<UActorIndex>(this, UActorIndex::StaticClass());

	LevelIndex->OnCurrentLevelChanged.AddUniqueDynamic(this, &UInteractableSpawnerSubsystem::IndexCurrentLevelChanged);

	//run scripts insted of helper if we can't get it first time?
}

void UInteractableSpawnerSubsystem::Deinitialize(){
	Super::Deinitialize();
}

void UInteractableSpawnerSubsystem::OnInteractableActorDropped(const TArray<UObject*>& DroppedObjects, const TArray<AActor*>& DroppedActors){
	if (!LoaderNameEdtiorBleuprint)
		LoaderNameEdtiorBleuprint = UEditorAssetLibrary::LoadAsset(FString(TEXT("/Script/Blutility.EditorUtilityWidgetBlueprint'/Game/Blueprints/UI/Editor/BP_LoaderNameEnter.BP_LoaderNameEnter'")));
	UE_LOGFMT(InteractableSpawnerSubsystem, Log, "Firing due to actor dropped");
	if (DroppedActors.Num() == 1) {
		IInteractable* interactable = Cast<IInteractable>(DroppedActors[0]);
		if (interactable) {
			if (IsValid(LoaderNameEdtiorBleuprint)) {
				LoaderNameEditorBlueprint = Cast<UEditorUtilityWidgetBlueprint>(LoaderNameEdtiorBleuprint);
				if (IsValid(LoaderNameEditorBlueprint)) {
					UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
					EditorUtilitySubsystem->SpawnAndRegisterTab(LoaderNameEditorBlueprint);
					LoaderNameEditor = Cast<ULoaderNameEnter>(LoaderNameEditorBlueprint->GetCreatedWidget());
					if (LoaderNameEditor) {
						LoaderNameEditor->LoaderNameEntered.AddUniqueDynamic(this, &UInteractableSpawnerSubsystem::CreateInteractableConfigs);
						LoaderNameEditor->LoaderNameChanged.AddUniqueDynamic(this, &UInteractableSpawnerSubsystem::CheckActorName);
					}
				}
			}
		}
	}
}

void UInteractableSpawnerSubsystem::OnMapOpened(const FString& Filename, bool bAsTemplate){
	FString level_name = ParseFileName(Filename);
	UE_LOGFMT(InteractableSpawnerSubsystem, Log, "Opened level {0}, is template {1}", level_name, bAsTemplate);
	if (!Helper) 
		Helper = UPythonEditorHelper::Get();
	if (Helper) 
		InitializeIndexes();
	if (LevelIndex->IsInitialised()) {
		if (!LevelIndex->HasLevel(level_name)) {
			Helper->InitLevelFolderStructure(level_name);
			LevelIndex->AddLevel(level_name);
		}
		LevelIndex->SetCurrentLevel(level_name);
	}

}

void UInteractableSpawnerSubsystem::IndexCurrentLevelChanged(const FString& level_name){
	if (!Helper) {
		Helper = UPythonEditorHelper::Get();
	}
	if (Helper) {
		TArray<FString> actors = Helper->GetActorsIndex(level_name);
		ActorIndex->BuildIndex(actors, level_name);
	}
}

void UInteractableSpawnerSubsystem::CreateInteractableConfigs(const FString& name){
	UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
	EditorUtilitySubsystem->UnregisterTabByID(LoaderNameEditorBlueprint->GetRegistrationName());
	if (Helper) {
		Helper->CreateInteractableConfigs(FString());
	}
}

void UInteractableSpawnerSubsystem::CheckActorName(const FString& Name){
	if (Name.IsEmpty()) {
		LoaderNameEditor->NameEmpty();
		return;
	}
	if (!Helper) {
		Helper = UPythonEditorHelper::Get();
		InitializeIndexes();
	}
	bool name_free = !ActorIndex->HasActor(Name);
	if (name_free) {
		LoaderNameEditor->NameDoesNotExist();
	}
	else {
		LoaderNameEditor->NameExists();
	}
}

void UInteractableSpawnerSubsystem::InitializeIndexes(){
	if (!LevelIndex->IsInitialised()) {
		TArray<FString> levels = Helper->GetLevelIndex();
		LevelIndex->BuildIndex(levels);
		LevelIndex->SetCurrentLevel(GEditor->GetEditorWorldContext().World()->GetName());
		UE_LOGFMT(InteractableSpawnerSubsystem, Log, "Index has level {0}", LevelIndex->HasLevel(levels[0]));
	}
	if (!ActorIndex->IsInitialised()) {
		TArray<FString> actors = Helper->GetActorsIndex(LevelIndex->GetCurrentLevel()); //TODO -- get world name, check for world in index, etc.
		ActorIndex->BuildIndex(actors, LevelIndex->GetCurrentLevel());
	}
}
