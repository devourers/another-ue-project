// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Logging/StructuredLog.h"

#include "Dialogue.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(DialogueLoading, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(DialogueAdvancment, Log, All);

//fwd declarations

struct FDialogueEntry;
struct FDialogueResponse;

USTRUCT()
struct FDialogueResult {
	GENERATED_BODY()
	//what checks finishing dialogue grants
};

USTRUCT()
struct FDialogueResponseConditions {
	GENERATED_BODY()
	//conditions for unlocking response
};

USTRUCT()
struct FDialogueEntry {
	GENERATED_BODY()
public:
	FName EntryName;
	FName EntryCharacter;
	FText EntryText;

	int IncomingResponse;
	TArray<int> Responses;

	FDialogueEntry() = default;

	FDialogueEntry(TSharedPtr<FJsonObject> obj);
	//construct from JSON or loader?
};

UCLASS()
class DISCO_ELYSIUM_RIPOFF_API UDialogueEntryWrapper : public UObject {
	GENERATED_BODY()
public:
	UPROPERTY()
	FDialogueEntry entry_;
};

USTRUCT()
struct FDialogueResponse {
	GENERATED_BODY()
public:
	FDialogueResponseConditions Conditions;
	int FromEntry;
	int Id;
	int ToEntry;
	FText ResponseText;

	FDialogueResponse() = default;
	FDialogueResponse(TSharedPtr<FJsonObject> obj);
	//construct from JSON or loader?
};

UCLASS()
class DISCO_ELYSIUM_RIPOFF_API UDialogueResponseWrapper : public UObject {
	GENERATED_BODY()
public:
	UPROPERTY()
	FDialogueResponse response_;
};

USTRUCT()
struct FDialogueHistory {
	GENERATED_BODY()
	//TODO
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDialogueStarted, class UDialogueEntryWrapper*, StartingEntry);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDialogueAdvanced, class UDialogueEntryWrapper*, NextEntry);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDialogueEnded);

/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API UDialogue : public UObject
{
	GENERATED_BODY()
	
	UDialogue() = default;
	UDialogue(UDialogue* other) = delete;

public:
	void StartDialogue();
	void AdvanceDialogue(int ChoosenResponse);
	void EndDialogue();

public:
	void LoadFromJson(const FString& path);

	UDialogueResponseWrapper* GetResponse(int response_id) const;

public: //delegates
	UPROPERTY()
	FDialogueStarted DialogueStarted;

	UPROPERTY()
	FDialogueAdvanced DialogueAdvanced;

	UPROPERTY()
	FDialogueEnded DialogueEnded;

private:
	FName Title;
	int CurrentStartingEntry = 0;
	int CurrentEntry;
	
	UPROPERTY()
	TArray<UDialogueEntryWrapper*> EntryWrappers;

	UPROPERTY()
	TArray<UDialogueResponseWrapper*> ReponseWrappers;

	TArray<FDialogueEntry> Entries;
	TArray<FDialogueResponse> Responses;
	FDialogueResult Result;

private: //flags
	bool bCanBeReinitated;
	bool bWasInitiated = false;

private: //json constants
	int ReEnterDialogueStartingEntry;
};
