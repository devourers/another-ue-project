// Fill out your copyright notice in the Description page of Project Settings.


#include "CodepadDeviceUI.h"

FReply UCodepadDeviceUI::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) {

	Super::NativeOnKeyDown(InGeometry, InKeyEvent);
	if (InKeyEvent.GetKey() == EKeys::Escape) {
		this->RemoveFromViewport();
		return FReply::Handled();
	}
	return FReply::Handled();
}