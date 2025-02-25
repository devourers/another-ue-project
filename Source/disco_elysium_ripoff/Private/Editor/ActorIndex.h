// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ActorIndex.generated.h"

/**
 * 
 */
UCLASS()
class UActorIndex : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void BuildIndex(const TArray<FString>& actors, const FString& level_name);

	UFUNCTION()
	void RemoveActor(const FString& actor);

	UFUNCTION()
	void AddActor(const FString& actor);

	UFUNCTION()
	bool HasActor(const FString& actor);

	UFUNCTION()
	bool IsInitialised() const;

	UFUNCTION()
	const FString& GetLevelName() const;


private:
	TSet<FString> Actors;
	bool is_initialized = false;
	FString LevelName;
};
