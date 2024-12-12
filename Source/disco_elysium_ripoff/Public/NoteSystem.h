// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "NoteEntry.h"

#include "UObject/NoExportTypes.h"
#include "NoteSystem.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNoteEntryAdded, class UNoteEntry*, Entry);

UCLASS()
class DISCO_ELYSIUM_RIPOFF_API UNoteSystem : public UObject
{
	GENERATED_BODY()
	
	UNoteSystem();

	UFUNCTION()
	void AddNoteToList(const FName& name, UNoteEntry* entry);

	UFUNCTION()
	bool HasNote(const FName& note);

	UFUNCTION()
	TArray<UNoteEntry*> GetAllNotes();

	FNoteEntryAdded OnNoteEntryAdded;

private:
	TMap<FName, UNoteEntry*> Notes;

};
