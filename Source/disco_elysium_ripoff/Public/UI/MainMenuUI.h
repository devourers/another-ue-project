// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuUI.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMainMenuUIButtonPressed, const FString&, ButtonName);

/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API UMainMenuUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

public:
	UPROPERTY()
	FMainMenuUIButtonPressed MainMenuUIButtonPressed;

protected:
	UFUNCTION()
	void OnContinueButtonClicked();

	UFUNCTION()
	void OnNewGameButtonClicked();

	UFUNCTION()
	void OnLoadGameButtonPressed();

	UFUNCTION()
	void OnOptionsButtonPressed();

	UFUNCTION()
	void OnQuitButtonPressed();

protected:
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ContinueButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* NewGameButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* LoadGameButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* OptionsButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* QuitButton;

private:

};
