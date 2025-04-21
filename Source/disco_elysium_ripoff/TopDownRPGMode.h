// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TopDownRPGMode.generated.h"

/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API ATopDownRPGMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ATopDownRPGMode();


	void BeginPlay() override;
};
