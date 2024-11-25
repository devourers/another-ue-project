// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseDeviceUI.h"
#include "CodepadDeviceUI.generated.h"

/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API UCodepadDeviceUI : public UBaseDeviceUI
{
	GENERATED_BODY()

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* CloseButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* InputBox;

	UPROPERTY(EditAnywhere, Category = InputButtons)
	TArray<class UButton*> InteractionButtons; //???

	UPROPERTY(EditAnywhere, Category = InputButtons)
	TMap<class UButton*, FKey> ButtonMappings; //???

	UPROPERTY(EditAnywhere, Category = InputButtons)
	TMap<FKey, FString> ValueMappings;
};
