// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownRPGMode.h"
#include "ProtagClass.h"
#include "PointAndClickPlayerController.h"
#include <Utils/SaveLoadGameInstanceSubsystem.h>


ATopDownRPGMode::ATopDownRPGMode() {
	PlayerControllerClass = APointAndClickPlayerController::StaticClass();

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_ProtagClass"));
	if (PlayerPawnBPClass.Class != nullptr) {
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Blueprints/BP_PointAndClickPlayerController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

void ATopDownRPGMode::BeginPlay(){

	USaveLoadGameInstanceSubsystem* saveload_handler = GetWorld()->GetGameInstance()->GetSubsystem<USaveLoadGameInstanceSubsystem>();

	if (saveload_handler) {
		saveload_handler->FinishSaveLoading(); //TODO logic for loading screens
	}

	Super::BeginPlay();
}
