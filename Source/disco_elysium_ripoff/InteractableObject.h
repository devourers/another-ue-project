// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "HoverWidgetComponent.h"
#include "InteractableObject.generated.h"

/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API AInteractableObject : public AInteractableActor
{
	GENERATED_BODY()

	AInteractableObject();

	virtual void BeginPlay() override;

	virtual void OnCursorOver(UPrimitiveComponent* component) override;

	virtual void OnCursorEnd(UPrimitiveComponent* component) override;

	virtual void OnActorSelectedAsDestination() override;

	virtual void OnActorAsDestinationReached(AActor* other_actor) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material, meta = (AllowPrivateAccess = "true"))
		UMaterial* UnselectedMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material, meta = (AllowPrivateAccess = "true"))
		UMaterial* SelectedMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, meta = (AllowPrivateAccess = "true"))
		UHoverWidgetComponent* tooltip;

private:
	
};
