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
	FString ResponseString = obj->GetStringField("text");
	if (ToEntry == -1)
		ResponseString += "\t [End]";
	ResponseText = FText::FromString(ResponseString);
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
		ReEnterDialogueStartingEntry = general->GetIntegerField("re_enter_dialogue_starting_entry");
		//parsing general stuff

		TArray<TSharedPtr<FJsonValue>> entries = json_object->GetArrayField("entries");
		for (size_t i = 0; i < entries.Num(); ++i) {
			UE_LOGFMT(DialogueLoading, Log, "Loaded entry {0}", i);
			TSharedPtr<FJsonObject> cur_entry = entries[i]->AsObject();
			Entries.Add(FDialogueEntry(cur_entry));
			UDialogueEntryWrapper* wrapper = NewObject<UDialogueEntryWrapper>();
			wrapper->entry_ = cur_entry;
			EntryWrappers.Add(wrapper);
		}

		TArray<TSharedPtr<FJsonValue>> responses = json_object->GetArrayField("responses");
		for (size_t i = 0; i < responses.Num(); ++i) {
			UE_LOGFMT(DialogueLoading, Log, "Loaded response {0}", i);
			TSharedPtr<FJsonObject> cur_response = responses[i]->AsObject();
			Responses.Add(FDialogueResponse(cur_response));
			UDialogueResponseWrapper* wrapper = NewObject<UDialogueResponseWrapper>();
			wrapper->response_ = cur_response;
			ReponseWrappers.Add(wrapper);
			wrapper->response_.Id = ReponseWrappers.Num() - 1;
		}
	}
	else {
		is_valid = false;
	}
}

UDialogueResponseWrapper* UDialogue::GetResponse(int response_id) const {
	return ReponseWrappers[response_id];
}

UDialogueEntryWrapper* UDialogue::GetEntry(int entry_id) const {
	return EntryWrappers[entry_id];
}

const FDialogueHistory& UDialogue::GetHistory() const {
	return History;
}

const FDialogueResult& UDialogue::GetResult() const{
	return Result;
}

bool UDialogue::IsValid() const{
	return is_valid;
}

void UDialogue::StartDialogue(){
	History.entries.Empty();
	History.responses.Empty();
	DialogueStarted.Broadcast(EntryWrappers[CurrentStartingEntry]);
	History.entries.Add(CurrentStartingEntry);
}

void UDialogue::AdvanceDialogue(int ChoosenResponse){
	History.responses.Add(ChoosenResponse);
	if (ReponseWrappers[ChoosenResponse]->response_.ToEntry == -1 || ReponseWrappers[ChoosenResponse]->response_.ToEntry == -2) {
		EndDialogue(ReponseWrappers[ChoosenResponse]->response_.ToEntry);
	}
	else {
		CurrentEntry = ReponseWrappers[ChoosenResponse]->response_.ToEntry;
		History.entries.Add(CurrentEntry);
		DialogueAdvanced.Broadcast(EntryWrappers[CurrentEntry]);
	}
}

void UDialogue::EndDialogue(int FinalResponse){
	if (ReEnterDialogueStartingEntry != -1) {
		CurrentStartingEntry = ReEnterDialogueStartingEntry;
	}
	if (FinalResponse == -1) {
		Result.IsSuccessful = true;
	}
	else if (FinalResponse == -2) {
		Result.IsSuccessful = false;
	}
	DialogueEnded.Broadcast();
}


