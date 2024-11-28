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

public:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	virtual void BindDevice(ADevice* device) override;

	virtual void SetupUIFromDeviceConfig(const FDeviceConfig& config) override;

protected:
	UFUNCTION()
	void OnButtonWasClicked(UButtonWithDelegate* Button);
	
	UFUNCTION()
	void OnCloseButtonClicked();

	UFUNCTION()
	void OnValueButtonPressed(const FKey& key);

	UFUNCTION()
	void ResetUI();

	void OnCorrectCode(UUMGSequencePlayer& player);

	void OnIncorrectCode(UUMGSequencePlayer& player);

private:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* CloseButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* InputBox;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* CorrectAnimation;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* IncorrectAnimation;

	UPROPERTY(EditAnywhere, Category = InputButtons, meta = (BindWidget))
	TMap<FName, FKey> InteractionButtonsNames;

	UPROPERTY()
	TArray<class UButtonWithDelegate*> InteractionButtons; //???

	UPROPERTY()
	TMap<class UButtonWithDelegate*, FKey> ButtonMappings; //???

	UPROPERTY(EditAnywhere, Category = InputButtons)
	TMap<FKey, FString> ValueMappings;

	UPROPERTY()
	ADevice* device_;

private:
	UPROPERTY()
	FString CorrectCode;

	UPROPERTY()
	int MaxCodepadCodeLength;

	UPROPERTY()
	bool bBlockInputs = false;
};
