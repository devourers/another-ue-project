// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NoteEntry.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum NoteType {
	eNT_Clue = 0 UMETA(DisplayName = "Clue"),
	eNT_DialogueChoice = 1 UMETA(DisplayName = "DialogueChoice")
};

UCLASS()
class DISCO_ELYSIUM_RIPOFF_API UNoteEntry : public UObject
{
	GENERATED_BODY()

public:
	UNoteEntry() = default;
	UNoteEntry(UNoteEntry* other);

	void LoadFromJson(const FString& path);

	FName GetTitle() { return Title; }
	TSet<FString> GetKeywords() { return Keywords; }
	FString GetDescription() { return Description; }
	NoteType GetType() { return Type; }

private:
	FName Title;
	TSet<FString> Keywords;
	
	FString Description;

	TEnumAsByte<NoteType> Type;
};
