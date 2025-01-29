// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueUI.generated.h"

/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API UDialogueUI : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	void LogConversation();

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UListView* ResponsesListView;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* CharacterName;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* EntryTextBlock;
};
