// Fill out your copyright notice in the Description page of Project Settings.


#include "NoteSystem.h"

UNoteSystem::UNoteSystem()
	:Super() {
	Notes.Empty(1);
}

void UNoteSystem::AddNoteToList(const FName& name, UNoteEntry* entry) {
	Notes.Add({ name, entry });
	OnNoteEntryAdded.Broadcast(entry);
}


bool UNoteSystem::HasNote(const FName& name) {
	return Notes.Find(name) != nullptr;
}


TArray<UNoteEntry*> UNoteSystem::GetAllNotes() {
	TArray<UNoteEntry*> res;
	for (auto pair : Notes) {
		res.Add(pair.Value);
	}
	return res;
}