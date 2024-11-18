// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"

#include "disco_elysium_ripoff.h"

#include "GameFramework/Actor.h"
#include "FadingActor.generated.h"

UCLASS()
class DISCO_ELYSIUM_RIPOFF_API AFadingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFadingActor();


UFUNCTION()
	void OnPlayerBehind();

UFUNCTION()
	void OnPlayerNoLongerBehind();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material, meta = (AllowPrivateAccess = "true"))
	UMaterial* SeeThroughMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material, meta = (AllowPrivateAccess = "true"))
	UMaterial* NormalMaterial;
};
