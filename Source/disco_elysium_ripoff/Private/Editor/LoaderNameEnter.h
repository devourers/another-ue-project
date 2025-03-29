// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#if WITH_EDITOR
#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "Logging/StructuredLog.h"
#include "InputCoreTypes.h"
#include "EditorUtilityWidgetComponents.h"
#include "LoaderNameEnter.generated.h"
#endif

DECLARE_LOG_CATEGORY_EXTERN(LoaderNameEnterLog, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLoaderNameEntered, const FString&, LoaderName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLoaderNameChanged, const FString&, LoaderName);

/**
 * 
 */
UCLASS()
class ULoaderNameEnter : public UEditorUtilityWidget
{
	GENERATED_BODY()

#if WITH_EDITOR

public:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

UFUNCTION()
	void NameExists();

UFUNCTION()
	void NameDoesNotExist();

UFUNCTION()
	void NameEmpty();

private:

UFUNCTION()
	void OnTextBoxTextCommited(const FText& Text, ETextCommit::Type CommitMethod);

UFUNCTION()
	void OnTextBoxTextChanged(const FText& Text);
#endif

#if WITH_EDITORONLY_DATA

public:
	UPROPERTY()
	FLoaderNameEntered LoaderNameEntered;

	UPROPERTY()
	FLoaderNameChanged LoaderNameChanged;

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UEditorUtilityEditableTextBox* TextBox;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* BadNameLabel;

private:
	bool safe_to_create = false;

#endif 

};
