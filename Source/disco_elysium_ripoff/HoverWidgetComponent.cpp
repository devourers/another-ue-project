// Fill out your copyright notice in the Description page of Project Settings.


#include "HoverWidgetComponent.h"

UHoverWidgetComponent::UHoverWidgetComponent() {
	
}

void UHoverWidgetComponent::SetDescription(const FString& description) {
	UHoverUserWidget* widget = Cast<UHoverUserWidget>(GetWidget());
	widget->SetDescription(description);
}

void UHoverWidgetComponent::SetHeader(const FString& header) {
	UHoverUserWidget* widget = Cast<UHoverUserWidget>(GetWidget());
	widget->SetHeader(header);
}