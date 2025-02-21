// Fill out your copyright notice in the Description page of Project Settings.


#include "Editor/InteractableSpawnerSubsystem.h"
#include "PythonEditorHelper.h"
#include "../../Public/Interactable.h"
#include "Subsystems/EditorActorSubsystem.h"

DEFINE_LOG_CATEGORY(InteractableSpawnerSubsystem);

void UInteractableSpawnerSubsystem::Initialize(FSubsystemCollectionBase& Collection){
	Collection.InitializeDependency(UEditorActorSubsystem::StaticClass());
	UE_LOGFMT(InteractableSpawnerSubsystem, Log, "Initialised interactable spawner subsystem");
	UEditorActorSubsystem* editor_actor_subsystem = GEditor->GetEditorSubsystem<UEditorActorSubsystem>();
	editor_actor_subsystem->OnNewActorsDropped.AddUniqueDynamic(this, &UInteractableSpawnerSubsystem::OnInteractableActorDropped);
}

void UInteractableSpawnerSubsystem::Deinitialize(){
	Super::Deinitialize();
}

void UInteractableSpawnerSubsystem::OnInteractableActorDropped(const TArray<UObject*>& DroppedObjects, const TArray<AActor*>& DroppedActors){
	UE_LOGFMT(InteractableSpawnerSubsystem, Log, "Firing due to actor dropped");
	if (DroppedActors.Num() == 1) {
		IInteractable* interactable = Cast<IInteractable>(DroppedActors[0]);
		UPythonEditorHelper* helper = UPythonEditorHelper::Get();
		if (interactable && helper) {
			helper->CreateInteractableConfigs(FString());
		}
	}
	
	GEditor->Exec(GetWorld(), TEXT("py test.py")); //todo -- create python bridge?
}
