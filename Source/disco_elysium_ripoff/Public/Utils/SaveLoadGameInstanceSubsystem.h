// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Logging/StructuredLog.h"
#include "SaveLoadGameInstanceSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(SaveLoadGameInstanceSubsystem, Log, All);

class UDERSaveGame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveGameSignature, class UDERSaveGame*, SaveObject);

/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API USaveLoadGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void WriteSaveGame(FString SlotName);

	UFUNCTION()
	void LoadSaveGame(FString SlotName);

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	UPROPERTY(BlueprintAssignable)
	FOnSaveGameSignature OnGameSaved;

	UPROPERTY(BlueprintAssignable)
	FOnSaveGameSignature OnGameLoaded;
};
