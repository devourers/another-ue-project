// Fill out your copyright notice in the Description page of Project Settings.


#include "HoverWidgetComponent.h"

UHoverWidgetComponent::UHoverWidgetComponent() {

}

void UHoverWidgetComponent::SetText(const FString& text) {
	Text = text;
}

void UHoverWidgetComponent::SetHeader(const FString& header) {
	Header = header;
}