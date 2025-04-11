// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PauseMenuUI.h"

#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
#include "../../PointAndClickPlayerController.h"

#include "Components/Button.h"

void UPauseMenuUI::NativeConstruct() {
	ResumeButton->OnClicked.AddUniqueDynamic(this, &UPauseMenuUI::OnResumeButtonClicked);
	SaveGameButton->OnClicked.AddUniqueDynamic(this, &UPauseMenuUI::OnSaveGameButtonClicked);
	LoadGameButton->OnClicked.AddUniqueDynamic(this, &UPauseMenuUI::OnLoadGameButtonPressed);
	OptionsButton->OnClicked.AddUniqueDynamic(this, &UPauseMenuUI::OnOptionsButtonPressed);
	MainMenuButton->OnClicked.AddUniqueDynamic(this, &UPauseMenuUI::OnMainMenuButtonPressed);
	QuitButton->OnClicked.AddUniqueDynamic(this, &UPauseMenuUI::OnQuitButtonPressed);
}

FReply UPauseMenuUI::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) {
	return FReply::Handled();
}

void UPauseMenuUI::BindController(APointAndClickPlayerController* controller){
	controller_ = controller;
}

void UPauseMenuUI::OnResumeButtonClicked() {
	PauseMenuUIButtonPressed.Broadcast("Continue");
}

void UPauseMenuUI::OnSaveGameButtonClicked() {
	PauseMenuUIButtonPressed.Broadcast("SaveGame");
}

void UPauseMenuUI::OnLoadGameButtonPressed() {
	PauseMenuUIButtonPressed.Broadcast("LoadGame");
}

void UPauseMenuUI::OnOptionsButtonPressed() {
	PauseMenuUIButtonPressed.Broadcast("Options");
}

void UPauseMenuUI::OnMainMenuButtonPressed(){
	PauseMenuUIButtonPressed.Broadcast("MainMenu");
}

void UPauseMenuUI::OnQuitButtonPressed() {
	PauseMenuUIButtonPressed.Broadcast("Quit");
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}