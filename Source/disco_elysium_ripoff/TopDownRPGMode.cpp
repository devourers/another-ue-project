// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownRPGMode.h"
#include "ProtagClass.h"
#include "PointAndClickPlayerController.h"


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
