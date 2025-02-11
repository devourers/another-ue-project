// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenuUI.h"
#include "Components/Button.h"

void UMainMenuUI::NativeConstruct(){
	ContinueButton->OnClicked.AddUniqueDynamic(this, &UMainMenuUI::OnContinueButtonClicked);
	NewGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenuUI::OnNewGameButtonClicked);
	LoadGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenuUI::OnLoadGameButtonPressed);
	OptionsButton->OnClicked.AddUniqueDynamic(this, &UMainMenuUI::OnOptionsButtonPressed);
	QuitButton->OnClicked.AddUniqueDynamic(this, &UMainMenuUI::OnQuitButtonPressed);
}

FReply UMainMenuUI::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent){
	return FReply::Handled();
}

void UMainMenuUI::OnContinueButtonClicked() {
	MainMenuUIButtonPressed.Broadcast("Continue");
}

void UMainMenuUI::OnNewGameButtonClicked() {
	MainMenuUIButtonPressed.Broadcast("NewGame");
}

void UMainMenuUI::OnLoadGameButtonPressed() {
	MainMenuUIButtonPressed.Broadcast("LoadGame");
}

void UMainMenuUI::OnOptionsButtonPressed() {
	MainMenuUIButtonPressed.Broadcast("Options");
}

void UMainMenuUI::OnQuitButtonPressed() {
	MainMenuUIButtonPressed.Broadcast("Quit");
}