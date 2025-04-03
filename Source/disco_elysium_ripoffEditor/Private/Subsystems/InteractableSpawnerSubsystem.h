// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#if WITH_EDITOR

#include "CoreMinimal.h"
#include "Logging/StructuredLog.h"
#include "EditorSubsystem.h"
#include "../Utils/LevelIndex.h"
#include "../Utils/ActorIndex.h"
#include "EditorUtilityWidgetBlueprint.h"
#include "../Python/PythonEditorHelper.h"
#include "../UI/LoaderNameEnter.h"
#include "InteractableSpawnerSubsystem.generated.h"

#endif

DECLARE_LOG_CATEGORY_EXTERN(InteractableSpawnerSubsystem, Log, All);

/**
 * 
 */

#if WITH_EDITOR

UCLASS()
class UInteractableSpawnerSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()


public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	UFUNCTION()
	void OnInteractableActorDropped(const TArray<UObject*>& DroppedObjects, const TArray<AActor*>& DroppedActors);

	UFUNCTION()
	void OnMapOpened(const FString& Filename, bool bAsTemplate);

	UFUNCTION()
	void IndexCurrentLevelChanged(const FString& level_name);

	UFUNCTION()
	void CreateInteractableConfigs(const FString& name);

	UFUNCTION()
	void CheckActorName(const FString& Name);


#if WITH_EDITORONLY_DATA
private:
	
	UPROPERTY()
	class UObject* LoaderNameEdtiorBleuprint;

	UPROPERTY()
	class UEditorUtilityWidgetBlueprint* LoaderNameEditorBlueprint;

	UPROPERTY()
	class ULoaderNameEnter* LoaderNameEditor;

	UPROPERTY()
	AActor* LastAddedActor;

	UPROPERTY()
	ULevelIndex* LevelIndex;

	UPROPERTY()
	UActorIndex* ActorIndex;

	UPROPERTY()
	UPythonEditorHelper* Helper;

#endif
};

#endif