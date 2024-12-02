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

	void SetShouldApplyOcclusion(bool isBehindWall, bool radius_condition);

	void SetOcclusionRadius(float DeltaTime);

	float GetCurrentOcclusionRadius() const;

	void BindPlayer(AActor* player);

private:
	AActor* player_;
	UMaterialParameterCollection* collection_;
	float OcclusionRadius = 0.3;
	float FadeDuration = 0.25;
	float CurrentOcclusionRadius = 0.0;
	bool __internal__ShouldApplyOcclusion = false;
	
};
