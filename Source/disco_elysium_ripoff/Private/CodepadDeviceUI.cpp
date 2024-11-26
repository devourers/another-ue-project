// Fill out your copyright notice in the Description page of Project Settings.


#include "CodepadDeviceUI.h"

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
	}
	return FReply::Handled();
}

void UCodepadDeviceUI::OnValueButtonPressed(const FKey& key) {
	if (ValueMappings.Contains(key)) {
		FString curr_text(InputBox->GetText().ToString());
		curr_text += ValueMappings[key];
		InputBox->SetText(FText::FromString(curr_text));
	}
}

void UCodepadDeviceUI::OnButtonWasClicked(UButtonWithDelegate* Button)
{
	if (ButtonMappings.Contains(Button)) {
		OnValueButtonPressed(ButtonMappings[Button]);
	}
}

void UCodepadDeviceUI::OnCloseButtonClicked() {
	this->RemoveFromViewport();
}