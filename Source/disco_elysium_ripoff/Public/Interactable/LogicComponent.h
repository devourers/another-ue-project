// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "../Dialogue/Dialogue.h"
#include "../LoreEntry.h"
#include "../InventoryEntry.h"
#include "../NoteEntry.h"

#include "LogicComponent.generated.h"

UENUM()
enum ELogicType {
	eLT_Dialogue UMETA(DisplayName = "Dialogue"),
	eLT_Lore UMETA(DisplayName = "Lore"),
	eLT_Inventory UMETA(DisplayName = "Inventory"),
	eLT_Note UMETA(DisplayName = "Note")
};

USTRUCT(BlueprintType)
struct DISCO_ELYSIUM_RIPOFF_API FLogicOrder {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = General)
	TArray<TEnumAsByte<ELogicType>> Order;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DISCO_ELYSIUM_RIPOFF_API ULogicComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULogicComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	UDialogue* GetDialogue();

	UFUNCTION()
	ULoreEntry* GetLoreEntry();

	UFUNCTION()
	UInventoryEntry* GetInventoryEntry();

	UFUNCTION()
	UNoteEntry* GetNoteEntry();

	UFUNCTION()
	const FLogicOrder& GetLogicOrder() const;

private:
	UPROPERTY()
	UDialogue* Dialogue;

	UPROPERTY()
	ULoreEntry* LoreEntry;

	UPROPERTY()
	UInventoryEntry* InventoryEntry;

	UPROPERTY()
	UNoteEntry* NoteEntry;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Order, meta = (AllowPrivateAccess = "true"))
	FLogicOrder LogicOrder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Loading, meta = (AllowPrivateAccess = "true"))
	FString LoaderName;

	UPROPERTY(VisibleAnywhere, Category = Loading)
	FString InventoryEntryPath;

	UPROPERTY(VisibleAnywhere, Category = Loading)
	FString DialoguePath;

	UPROPERTY(VisibleAnywhere, Category = Loading)
	FString LoreEntryPath;

	UPROPERTY(VisibleAnywhere, Category = Loading)
	FString NoteEntryPath;
};
