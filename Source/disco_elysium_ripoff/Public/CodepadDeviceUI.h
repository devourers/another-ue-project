// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseDeviceUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "ButtonWithDelegate.h"
#include "CodepadDeviceUI.generated.h"

/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API UCodepadDeviceUI : public UBaseDeviceUI
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	UFUNCTION()
	void OnButtonWasClicked(UButtonWithDelegate* Button);
	
	UFUNCTION()
	void OnCloseButtonClicked();

	UFUNCTION()
	void OnValueButtonPressed(const FKey& key);

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* CloseButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* InputBox;

	UPROPERTY(EditAnywhere, Category = InputButtons, meta = (BindWidget))
	TMap<FName, FKey> InteractionButtonsNames;

	UPROPERTY()
	TArray<class UButtonWithDelegate*> InteractionButtons; //???

	UPROPERTY()
	TMap<class UButtonWithDelegate*, FKey> ButtonMappings; //???

	UPROPERTY(EditAnywhere, Category = InputButtons)
	TMap<FKey, FString> ValueMappings;
};
