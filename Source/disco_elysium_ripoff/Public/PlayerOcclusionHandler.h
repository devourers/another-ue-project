// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerOcclusionHandler.generated.h"

/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API UPlayerOcclusionHandler : public UObject
{
	GENERATED_BODY()

public:
	UPlayerOcclusionHandler();

	UPlayerOcclusionHandler(AActor* player);

	void SetCharacterPosition();

	void SetShouldApplyOcclusion(bool to_apply);

	void SetOcclusionRadius(float DeltaTime);

	void BindPlayer(AActor* player);

private:
	AActor* player_;
	UMaterialParameterCollection* collection_;
	float OcclusionRadius = 0.1;
	float FadeDuration = 0.5;
	float CurrentOcclusionRadius = 0.0;
	
};
