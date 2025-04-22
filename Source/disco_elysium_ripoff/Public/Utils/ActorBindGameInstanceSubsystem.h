// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Logging/StructuredLog.h"
#include "ActorBindGameInstanceSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(ActorBindGameInstanceSubsystem, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBindActors);

/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API UActorBindGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	UPROPERTY(BlueprintAssignable)
	FBindActors BindActors;

};
