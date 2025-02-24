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

void UInteractableSpawnerSubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Collection.InitializeDependency(UEditorActorSubsystem::StaticClass());
	//Collection.InitializeDependency(ULevelEditorSubsystem::StaticClass());

	UE_LOGFMT(InteractableSpawnerSubsystem, Log, "Initialised interactable spawner subsystem");

	UEditorActorSubsystem* editor_actor_subsystem = GEditor->GetEditorSubsystem<UEditorActorSubsystem>();
	editor_actor_subsystem->OnNewActorsDropped.AddUniqueDynamic(this, &UInteractableSpawnerSubsystem::OnInteractableActorDropped);

	//ULevelEditorSubsystem* level_editor_subsystem = GEditor->GetEditorSubsystem<ULevelEditorSubsystem>();
	//level_editor_subsystem->OnMapOpened.AddUniqueDynamic(this, &) TODO

	LevelIndex = NewObject<ULevelIndex>(this, ULevelIndex::StaticClass());
	ActorIndex = NewObject<UActorIndex>(this, UActorIndex::StaticClass());
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
	//GEditor->Exec(GetWorld(), TEXT("py test.py")); //todo -- create python bridge?
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
		UE_LOGFMT(InteractableSpawnerSubsystem, Log, "Index has level {0}", LevelIndex->HasLevel(levels[0]));
	}
	if (!ActorIndex->IsInitialised()) {
		TArray<FString> actors = Helper->GetActorsIndex(GEditor->GetEditorWorldContext().World()->GetName()); //TODO -- get world name, check for world in index, etc.
		ActorIndex->BuildIndex(actors); 
	}
}
