// Fill out your copyright notice in the Description page of Project Settings.


#include "Editor/InteractableSpawnerSubsystem.h"
#include "EditorUtilitySubsystem.h"
#include "PythonEditorHelper.h"
#include "EditorAssetLibrary.h"
#include "EngineUtils.h"
#include "EditorUtilitySubsystem.h"
#include "../../Public/Interactable.h"
#include "Subsystems/EditorActorSubsystem.h"

DEFINE_LOG_CATEGORY(InteractableSpawnerSubsystem);

void UInteractableSpawnerSubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Collection.InitializeDependency(UEditorActorSubsystem::StaticClass());
	UE_LOGFMT(InteractableSpawnerSubsystem, Log, "Initialised interactable spawner subsystem");
	UEditorActorSubsystem* editor_actor_subsystem = GEditor->GetEditorSubsystem<UEditorActorSubsystem>();
	editor_actor_subsystem->OnNewActorsDropped.AddUniqueDynamic(this, &UInteractableSpawnerSubsystem::OnInteractableActorDropped);
	LoaderNameEdtiorBleuprint = UEditorAssetLibrary::LoadAsset(FString(TEXT("/Script/Blutility.EditorUtilityWidgetBlueprint'/Game/Blueprints/UI/Editor/BP_LoaderNameEnter1.BP_LoaderNameEnter1'")));
	LevelIndex = NewObject<ULevelIndex>(this, ULevelIndex::StaticClass());
}

void UInteractableSpawnerSubsystem::Deinitialize(){
	Super::Deinitialize();
}

void UInteractableSpawnerSubsystem::OnInteractableActorDropped(const TArray<UObject*>& DroppedObjects, const TArray<AActor*>& DroppedActors){
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
	if (!Helper) {
		Helper = UPythonEditorHelper::Get();
		//TODO -- inits
		TArray<FString> levels = Helper->GetLevelIndex();
		LevelIndex->BuildIndex(levels);
		UE_LOGFMT(InteractableSpawnerSubsystem, Log, "Index has level {0}", LevelIndex->HasLevel(levels[0]));
	}
	if (Helper) {
		
		Helper->CreateInteractableConfigs(FString());
	}
}

void UInteractableSpawnerSubsystem::CheckActorName(const FString& Name){
	
	bool name_free = fmod(Name.Len(), 2) == 0; //todo -- run script for checking if exist
	//there may be a probl
	// em if we type to fast and script is too slow -- build index of those files here?
	if (name_free) {
		LoaderNameEditor->NameDoesNotExist();
	}
	else {
		LoaderNameEditor->NameExists();
	}
}
