// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Dialogue.h"
#include "DialogueResponseListView.generated.h"

/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API UDialogueResponseListView : public UUserWidget
{
	GENERATED_BODY()
	
UFUNCTION()
	void OnResponseAdded(UDialogueResponseWrapper* response);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UListView* DialogueResponseListView;

};
