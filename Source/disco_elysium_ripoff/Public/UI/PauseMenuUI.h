// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "PauseMenuUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPauseMenuUIButtonPressed, const FString&, ButtonName);

class APointAndClickPlayerController;

/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API UPauseMenuUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

public:
	UPROPERTY()
	FPauseMenuUIButtonPressed PauseMenuUIButtonPressed;

	UFUNCTION()
	void BindController(APointAndClickPlayerController* controller);

protected:
	UFUNCTION()
	void OnResumeButtonClicked();

	UFUNCTION()
	void OnSaveGameButtonClicked();

	UFUNCTION()
	void OnLoadGameButtonPressed();

	UFUNCTION()
	void OnOptionsButtonPressed();

	UFUNCTION()
	void OnMainMenuButtonPressed();

	UFUNCTION()
	void OnQuitButtonPressed();

protected:
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ResumeButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* SaveGameButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* LoadGameButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* OptionsButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* MainMenuButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* QuitButton;

private:
	
	UPROPERTY()
	APointAndClickPlayerController* controller_;
};
