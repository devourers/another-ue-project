// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "EditorUtilityWidgetComponents.h"
#include "LoaderNameEnter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLoaderNameEntered, const FString&, LoaderName);

/**
 * 
 */
UCLASS()
class ULoaderNameEnter : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

public:
	UPROPERTY()
	FLoaderNameEntered LoaderNameEntered;

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UEditorUtilityEditableTextBox* TextBox;

private:
};
