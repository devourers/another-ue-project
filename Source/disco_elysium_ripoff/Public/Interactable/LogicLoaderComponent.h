// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LogicLoaderComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DISCO_ELYSIUM_RIPOFF_API ULogicLoaderComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULogicLoaderComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Loading, meta = (AllowPrivateAccess = "true"))
	FString LoaderName;

	UPROPERTY(VisibleAnywhere, Category = Loading)
	FString InventoryEntryPath;

	UPROPERTY(VisibleAnywhere, Category = Loading)
	FString DialoguePath;

	UPROPERTY(VisibleAnywhere, Category = Loading)
	FString LoreEntryPath;
};
