// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIPointOfInterest.generated.h"

UCLASS()
class DISCO_ELYSIUM_RIPOFF_API AAIPointOfInterest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIPointOfInterest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	const FString& GetChannel() const;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = General, meta = (AllowPrivateAccess = "true"))
	FString Channel;
};
