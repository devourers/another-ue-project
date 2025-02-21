// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine.h"
#include "PythonEditorHelper.generated.h"

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
	void CreateInteractableConfigs(const FString& LoaderName) const;
	
};
