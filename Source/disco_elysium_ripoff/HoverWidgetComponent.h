// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "HoverUserWidget.h"
#include "HoverWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API UHoverWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
	UHoverWidgetComponent();

public:
UFUNCTION()
	void SetHeader(const FString& header);

UFUNCTION()
	void SetDescription(const FString& text);

};
