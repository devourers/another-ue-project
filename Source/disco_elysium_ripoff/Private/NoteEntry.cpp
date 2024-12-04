// Fill out your copyright notice in the Description page of Project Settings.


#include "NoteEntry.h"

UNoteEntry::UNoteEntry(UNoteEntry* other) {
	Title = other->GetTitle();
	Keywords = other->GetKeywords();
	Description = other->GetDescription();
}

void UNoteEntry::LoadFromJson(const FString& path) {
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString("Loading Note"));

	FString loaded_file;
	FFileHelper::LoadFileToString(loaded_file, *path);
	TSharedRef<TJsonReader<>> json_reader = TJsonReaderFactory<>::Create(loaded_file);
	TSharedPtr<FJsonObject> json_object = MakeShareable(new FJsonObject());
	if (FJsonSerializer::Deserialize(json_reader, json_object) &&
		json_object.IsValid()) {
		Title = FName(json_object->GetStringField("Title"));
		TArray<TSharedPtr<FJsonValue>> keywords = json_object->GetArrayField("Keywords");
		for (size_t i = 0; i < keywords.Num(); ++i) {
			Keywords.Add(keywords[i]->AsString());
		}
		Description = json_object->GetStringField("Description");
	}
}