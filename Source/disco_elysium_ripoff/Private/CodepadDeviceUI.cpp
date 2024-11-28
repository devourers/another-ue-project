// Fill out your copyright notice in the Description page of Project Settings.


#include "CodepadDeviceUI.h"
#include "Animation/UMGSequencePlayer.h"
#include "Device.h"

void UCodepadDeviceUI::NativeConstruct() {
	Super::NativeConstruct();

	InteractionButtons.Empty();
	ButtonMappings.Empty();
	
	for (auto Pair :  InteractionButtonsNames) {
		UButtonWithDelegate* but = Cast<UButtonWithDelegate>(GetWidgetFromName(Pair.Key));
		InteractionButtons.Add(but);
		ButtonMappings.Add({ but, Pair.Value });
	}

	for (UButtonWithDelegate* Button : InteractionButtons)
	{
		Button->OnClickedDelegate.AddUniqueDynamic(this, &ThisClass::OnButtonWasClicked);
	}

	CloseButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnCloseButtonClicked);
}

FReply UCodepadDeviceUI::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) {
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if (InKeyEvent.GetKey() == EKeys::C) {
		OnCloseButtonClicked();
		return FReply::Handled();
	}
	else {
		OnValueButtonPressed(InKeyEvent.GetKey());
		return FReply::Handled();
	}
}

void UCodepadDeviceUI::OnValueButtonPressed(const FKey& key) {
	if (ValueMappings.Contains(key) && !bBlockInputs) {
		FString curr_text(InputBox->GetText().ToString());
		curr_text += ValueMappings[key];
		if (curr_text.Len() == MaxCodepadCodeLength) {
			if (curr_text == CorrectCode) {
				InputBox->SetText(FText::FromString(curr_text));
				bBlockInputs = true;
				if (CorrectAnimation) {
					UUMGSequencePlayer* sequence_player = PlayAnimation(CorrectAnimation, 0.0F, 2);
					sequence_player->OnSequenceFinishedPlaying().AddUObject(this, &UCodepadDeviceUI::OnCorrectCode);
				}
			}
			else {
				bBlockInputs = true;
				InputBox->SetText(FText::FromString(TEXT("ERROR")));
				if (IncorrectAnimation) {
					PlayAnimation(IncorrectAnimation, 0.0F, 2);
					ActiveSequencePlayers.Last()->OnSequenceFinishedPlaying().AddUObject(this, &UCodepadDeviceUI::OnIncorrectCode);
				}
			}
		}
		else {
			InputBox->SetText(FText::FromString(curr_text));
		}
	}
}

void UCodepadDeviceUI::OnButtonWasClicked(UButtonWithDelegate* Button)
{
	if (ButtonMappings.Contains(Button)) {
		OnValueButtonPressed(ButtonMappings[Button]);
	}
}

void UCodepadDeviceUI::OnCloseButtonClicked() {
	if (device_)
		device_->CloseUI();
}

void UCodepadDeviceUI::BindDevice(ADevice* device) {
	device_ = device;
}

void UCodepadDeviceUI::SetupUIFromDeviceConfig(const FDeviceConfig& config) {
	CorrectCode = config.CodepadCode;
	MaxCodepadCodeLength = config.MaxCodepadCodeLength;
}

void UCodepadDeviceUI::OnCorrectCode(UUMGSequencePlayer& player) {
	//TODO: send signal to device
	FDeviceUISignal signal;
	signal.SignalType = EDeviceSignalType::EDST_CodepadCorrectCode;
	OnSignalSent(signal);
	device_->CloseUI();
}

void UCodepadDeviceUI::OnIncorrectCode(UUMGSequencePlayer& player) {
	//TODO: send signal to device
	FDeviceUISignal signal;
	signal.SignalType = EDeviceSignalType::EDST_CodepadIncorrectCode;
	OnSignalSent(signal);
	ResetUI();
}

void UCodepadDeviceUI::ResetUI() {
	bBlockInputs = false;
	InputBox->SetText(FText());
}