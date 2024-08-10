// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "InteractableObject.generated.h"

/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API AInteractableObject : public AInteractableActor
{
	GENERATED_BODY()

	AInteractableObject();

	virtual void OnCursorOver(UPrimitiveComponent* component) override;

	virtual void OnCursorEnd(UPrimitiveComponent* component) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material, meta = (AllowPrivateAccess = "true"))
		UMaterial* UnselectedMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material, meta = (AllowPrivateAccess = "true"))
		UMaterial* SelectedMaterial;
	
};
