// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "../Dialogue/Dialogue.h"
#include "../LoreEntry.h"
#include "../InventoryEntry.h"
#include "../NoteEntry.h"

#include "LogicComponent.generated.h"

class APointAndClickPlayerController;
class AProtagClass;

UENUM()
enum ELogicOrder {
	eLO_DiagloueFirst UMETA(DisplayName = "Dialogue first"),
	eLO_DialogueAfter UMETA(DisplayName = "Dialogue after")
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

	UFUNCTION(BlueprintCallable)
	UDialogue* GetDialogue();

	UFUNCTION()
	ULoreEntry* GetLoreEntry();

	UFUNCTION()
	UInventoryEntry* GetInventoryEntry();

	UFUNCTION()
	UNoteEntry* GetNoteEntry();

	UFUNCTION()
	ELogicOrder GetLogicOrder() const;

	UFUNCTION()
	const FString& GetLoaderName() const;

	UFUNCTION()
	void SetLoaderName(const FString& loader_name);

	UFUNCTION()
	const FString& GetWorldName() const;

	UFUNCTION()
	const FString& GetDisplayedName() const;

	UFUNCTION()
	class UDialogueUI* CreateDialogueUI(APointAndClickPlayerController* PCC, AProtagClass* protag);

	UFUNCTION()
	void CloseDialogueUI();

private:
	UPROPERTY()
	UDialogue* Dialogue;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UDialogueUI> DialogueUIClass;

	UPROPERTY()
	class UDialogueUI* DialogueUI;

	UPROPERTY()
	ULoreEntry* LoreEntry;

	UPROPERTY()
	UInventoryEntry* InventoryEntry;

	UPROPERTY()
	UNoteEntry* NoteEntry;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Order, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<ELogicOrder> LogicOrder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = General, meta = (AllowPrivateAccess = "true"))
	FString DisplayedName;

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

	UPROPERTY(VisibleAnywhere)
	FString WorldName;
};
