// Fill out your copyright notice in the Description page of Project Settings.


#include "HoverUserWidget.h"
#include "Components/TextBlock.h"


void UHoverUserWidget::SetHeader(const FString& header) {
	if (Header) {
		Header->SetText(FText::FromString(header));
	}
}

void UHoverUserWidget::SetDescription(const FString& description) {
	if (Description) {
		Description->SetText(FText::FromString(description));
	}
}