// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenuUI.h"

#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <Utils/DERSaveGame.h>

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
	UGameplayStatics::OpenLevel(GetWorld(), FName("/Game/Levels/TestLevel"));
}

void UMainMenuUI::OnNewGameButtonClicked() {
	MainMenuUIButtonPressed.Broadcast("NewGame");
	UGameplayStatics::OpenLevel(GetWorld(), FName("/Game/Levels/GameLevels/Chapter1/L_CH1_ProtagFlat"));
}

void UMainMenuUI::OnLoadGameButtonPressed() {
	MainMenuUIButtonPressed.Broadcast("LoadGame");
	if (UDERSaveGame* LoadedGame = Cast<UDERSaveGame>(UGameplayStatics::LoadGameFromSlot("TestFromPause", 0))) {
		UE_LOG(LogTemp, Warning, TEXT("LOADED: %s"), *FString("game"));
	}
}

void UMainMenuUI::OnOptionsButtonPressed() {
	MainMenuUIButtonPressed.Broadcast("Options");
}

void UMainMenuUI::OnQuitButtonPressed() {
	MainMenuUIButtonPressed.Broadcast("Quit");
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}