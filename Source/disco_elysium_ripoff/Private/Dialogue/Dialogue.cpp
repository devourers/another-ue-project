// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/Dialogue.h"

DEFINE_LOG_CATEGORY(DialogueLoading)
DEFINE_LOG_CATEGORY(DialogueAdvancment)

FDialogueEntry::FDialogueEntry(TSharedPtr<FJsonObject> obj) {
	EntryName = FName(obj->GetStringField("name"));
	EntryCharacter = FName(obj->GetStringField("character"));
	EntryText = FText::FromString(obj->GetStringField("text"));
	IncomingResponse = obj->GetIntegerField("incoming_response");
	TArray<TSharedPtr<FJsonValue>> responses_ = obj->GetArrayField("responses");
	for (size_t i = 0; i < responses_.Num(); ++i) {
		Responses.Add(responses_[i]->AsNumber());
	}
}

FDialogueResponse::FDialogueResponse(TSharedPtr<FJsonObject> obj) {
	//conditions
	FromEntry = obj->GetIntegerField("from");
	ToEntry = obj->GetIntegerField("to");
	ResponseText = FText::FromString(obj->GetStringField("text"));
}

void UDialogue::LoadFromJson(const FString& path) {
	FString loaded_file;
	FFileHelper::LoadFileToString(loaded_file, *path);
	TSharedRef<TJsonReader<>> json_reader = TJsonReaderFactory<>::Create(loaded_file);
	TSharedPtr<FJsonObject> json_object = MakeShareable(new FJsonObject());
	if (FJsonSerializer::Deserialize(json_reader, json_object) &&
		json_object.IsValid()) {
		TSharedPtr<FJsonObject> general = json_object->GetObjectField("general");
		bCanBeReinitated = bool(general->GetBoolField("can_be_reinitiated"));
		Title = FName(general->GetStringField("title"));
		//parsing general stuff

		TArray<TSharedPtr<FJsonValue>> entries = json_object->GetArrayField("entries");
		for (size_t i = 0; i < entries.Num(); ++i) {
			UE_LOGFMT(DialogueLoading, Log, "Loaded entry {0}", i);
			TSharedPtr<FJsonObject> cur_entry = entries[i]->AsObject();
			Entries.Add(FDialogueEntry(cur_entry));
		}

		TArray<TSharedPtr<FJsonValue>> responses = json_object->GetArrayField("responses");
		for (size_t i = 0; i < responses.Num(); ++i) {
			UE_LOGFMT(DialogueLoading, Log, "Loaded response {0}", i);
			TSharedPtr<FJsonObject> cur_response = responses[i]->AsObject();
			Responses.Add(FDialogueResponse(cur_response));
		}
	}
}

void UDialogue::StartDialogue(){
	//emit delegates?
}

void UDialogue::AdvanceDialogue(int ChoosenResponse){
	if (Responses[ChoosenResponse].ToEntry == -1) {
		EndDialogue();
	}
	else {
		CurrentEntry = Responses[ChoosenResponse].ToEntry;
	}
}

void UDialogue::EndDialogue(){
	if (ReEnterDialogueStartingEntry != -1) {
		CurrentStartingEntry = ReEnterDialogueStartingEntry;
	}
}


