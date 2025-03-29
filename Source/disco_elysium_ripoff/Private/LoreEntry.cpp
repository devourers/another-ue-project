// Fill out your copyright notice in the Description page of Project Settings.


#include "LoreEntry.h"

void ULoreEntry::LoadFromJson(const FString& path) {
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString("Loading Lore"));

	FString loaded_file;
	FFileHelper::LoadFileToString(loaded_file, *path);
	TSharedRef<TJsonReader<>> json_reader = TJsonReaderFactory<>::Create(loaded_file);
	TSharedPtr<FJsonObject> json_object = MakeShareable(new FJsonObject());
	if (FJsonSerializer::Deserialize(json_reader, json_object) &&
		json_object.IsValid()) {
		Title = FName(json_object->GetStringField("Title"));
		Subcategory = FName(json_object->GetStringField("Subcategory"));
		Category = FName(json_object->GetStringField("Category"));
		TArray<TSharedPtr<FJsonValue>> keywords = json_object->GetArrayField("Keywords");
		for (size_t i = 0; i < keywords.Num(); ++i) {
			Keywords.Add(keywords[i]->AsString());
		}
		TSharedPtr<FJsonObject> content = json_object->GetObjectField("Content");
		for (auto& value : content->Values) {
			Content.Add(TTuple<FName, FString>(value.Key, value.Get<FString>()));
		}
	}
	else {
		is_valid = false;
	}
}

bool ULoreEntry::IsValid() const{
	return is_valid;
}
