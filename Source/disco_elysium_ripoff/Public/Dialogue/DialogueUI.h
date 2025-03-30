// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Dialogue.h"
#include "../Interactable.h"

#include "DialogueUI.generated.h"

class AProtagClass;

/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API UDialogueUI : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	void LogConversation();

	void BindDialogue(UDialogue* dalogue);

	void BindLogicComponent(ULogicComponent* logic);

	void BindProtag(AProtagClass* protag);

protected:
	UFUNCTION()
	void OnResponseSelectionChanged(UObject* SelectedObject);

	UFUNCTION()
	void OnDialogueStarted(UDialogueEntryWrapper* entry);

	UFUNCTION()
	void OnDialogueAdvanced(UDialogueEntryWrapper* entry);

	UFUNCTION()
	void OnDialogueEnded();

	UFUNCTION()
	bool ConditionsMet(UDialogueResponseWrapper* response) const;

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UListView* ResponsesListView;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* CharacterName;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* EntryTextBlock;

private:
	UPROPERTY()
	UDialogue* dialogue_;

	UPROPERTY()
	ULogicComponent* logic_;

	UPROPERTY()
	AProtagClass* protag_;
};
