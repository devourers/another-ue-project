// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Interactable.h"
#include "../disco_elysium_ripoff.h"
#include "Components/SphereComponent.h"
#include "Components/TimelineComponent.h"
#include "Navigation/NavLinkProxy.h"

#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class DISCO_ELYSIUM_RIPOFF_API ADoor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ToggleHighlight(bool to_toggle) override;

	virtual void Interact() override;

	virtual void OnCursorOver(UPrimitiveComponent* component) override;

	virtual void OnCursorEnd(UPrimitiveComponent* component) override;

	virtual void OnInteractableAsDestinationReached(AActor* other_actor) override;

	virtual void OnInteractableSelectedAsDestination() override;

	virtual USphereComponent* GetInteractionHitbox() override;

	UFUNCTION()
	void OpenDoor(float Value);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* DoorFrameMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	USphereComponent* InteractionHitbox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	UCurveFloat* OpeningCurve;

private:
	FTimeline OpeningTimeline;
	bool bIsDoorClosed = true;
	bool bIsDoorLocked = false;
	float DoorOpeningAngle = 90.0f;
};
