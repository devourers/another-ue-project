// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Interactable.h"
#include "LoreEntry.h"
#include "InventoryEntry.h"

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

	virtual void Interact() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	FName DisplayedName; //name for gameplay purposes

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Loading, meta = (AllowPrivateAccess = "true"))
	FName LoaderName; //name for loading items from configs 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EItemType> Type;

	UPROPERTY()
	ULoreEntry* LoreEntry; //Associated with item lore entry. Loads from JSON

	UPROPERTY(VisibleAnywhere, Category = Loading)
	FString LoreEntryPath; //sets automatically in constructor via level ID and object name

	UPROPERTY()
	UInventoryEntry* InventoryEntry;
};