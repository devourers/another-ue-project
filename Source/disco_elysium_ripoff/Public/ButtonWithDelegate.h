// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonWithDelegate.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDERClickedSignature, class UButtonWithDelegate*, Button);

/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API UButtonWithDelegate : public UUserWidget
{
	GENERATED_BODY()

public:
	// Bind a function with the signature "void OnClicked(UBUIUWButton* Button);
	FDERClickedSignature OnClickedDelegate;

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget), EditAnywhere)
	class UButton* MainButton;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ButtonText;

	UPROPERTY(EditAnywhere)
	FString button_text;

	UFUNCTION()
	void OnButtonClicked();
	
};
