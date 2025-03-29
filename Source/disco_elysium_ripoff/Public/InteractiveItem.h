// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../disco_elysium_ripoff.h"

#include "Interactable.h"
#include "LoreEntry.h"
#include "InventoryEntry.h"
#include "Dialogue/Dialogue.h"

#include "Components/SphereComponent.h"

#include "GameFramework/Actor.h"
#include "InteractiveItem.generated.h"

UENUM(BlueprintType)
enum EItemType{
	eIT_Pickable = 0 UMETA(DisplayName = "Pickable"),
	eIT_Flair = 1 UMETA(DisplayName = "Flair")
};


UCLASS()
class DISCO_ELYSIUM_RIPOFF_API AInteractiveItem : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractiveItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ToggleHighlight(bool to_toggle) override;

	virtual void InternalInteract(AActor* other_actor) override;

	virtual void OnCursorOver(UPrimitiveComponent* component) override;

	virtual void OnCursorEnd(UPrimitiveComponent* component) override;

	virtual void OnInteractableAsDestinationReached(AActor* other_actor) override;

	virtual void OnInteractableSelectedAsDestination() override;

	virtual USphereComponent* GetInteractionHitbox() override;

	UFUNCTION(BlueprintCallable)
	virtual ULogicComponent* GetLogicComponent() override;

	virtual UMainGameInstanceSubsystem* GetHandler() override;

	virtual AProtagClass* GetProtag() override;

	virtual void BindProtag(AActor* other_actor) override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EItemType> Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	USphereComponent* InteractionHitbox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Logic, meta = (AllowPrivateAccess = "true"))
	ULogicComponent* LogicComponent;

	UPROPERTY()
	AProtagClass* protag_;

	UPROPERTY()
	UMainGameInstanceSubsystem* handler_;
};
