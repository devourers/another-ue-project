// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LevelIndex.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCurrentLevelChanged, const FString&, Level);

/**
 * 
 */
UCLASS()
class ULevelIndex : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void BuildIndex(const TArray<FString>& levels);

	UFUNCTION()
	void RemoveLevel(const FString& level);

	UFUNCTION()
	void AddLevel(const FString& level);

	UFUNCTION()
	bool HasLevel(const FString& level);

	UFUNCTION()
	bool IsInitialised() const;

	UFUNCTION()
	const FString& GetCurrentLevel() const;

	UFUNCTION()
	void SetCurrentLevel(const FString& level);

public:
	FCurrentLevelChanged OnCurrentLevelChanged;

private:
	TSet<FString> Levels;
	bool is_initialized = false;
	FString CurrentLevel;
	
};
