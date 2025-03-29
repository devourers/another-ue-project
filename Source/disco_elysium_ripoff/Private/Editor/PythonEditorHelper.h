// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#if WITH_EDITOR
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine.h"
#include "PythonEditorHelper.generated.h"
#endif
/**
 * 
 */
UCLASS(Blueprintable)
class UPythonEditorHelper : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Python)
	static UPythonEditorHelper* Get();

	UFUNCTION(BlueprintImplementableEvent, Category = Python)
	void CreateInteractableConfigs(const FString& LevelName, const FString& LoaderName) const;

	UFUNCTION(BlueprintImplementableEvent, Category = Python)
	void CreateLevelConfigStructure(const FString& LevelName) const;
	
	UFUNCTION(BlueprintImplementableEvent, Category = Python)
	TArray<FString> GetLevelIndex() const;

	UFUNCTION(BlueprintImplementableEvent, Category = Python)
	TArray<FString> GetActorsIndex(const FString& level) const;

	UFUNCTION(BlueprintImplementableEvent, Category = Python)
	void InitLevelFolderStructure(const FString& level_name) const;
	
};
