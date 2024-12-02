// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProtagOcclusionHandler.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DISCO_ELYSIUM_RIPOFF_API UProtagOcclusionHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UProtagOcclusionHandler();

	UFUNCTION()
	void SetCharacterPosition();

	UFUNCTION()
	void SetShouldApplyOcclusion(bool isBehindWall, bool radius_condition);

	UFUNCTION()
	void SetOcclusionRadius(float DeltaTime);

	UFUNCTION()
	float GetCurrentOcclusionRadius() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UMaterialParameterCollection* collection_ = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Occlusion, meta = (AllowPrivateAccess = "true"))
	float OcclusionRadius = 0.3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Occlusion, meta = (AllowPrivateAccess = "true"))
	float FadeDuration = 0.25;

	float CurrentOcclusionRadius = 0.0;
	bool __internal__ShouldApplyOcclusion = false;
};
