// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonWithDelegate.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UButtonWithDelegate::NativeConstruct()
{
	Super::NativeConstruct();
	if (MainButton) {
		MainButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnButtonClicked);
	}
	if (ButtonText) {
		ButtonText->SetText(FText::FromString(button_text));
	}
}

void UButtonWithDelegate::OnButtonClicked()
{
	OnClickedDelegate.Broadcast(this);
}
