// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownRPGMode.h"
#include "ProtagClass.h"
#include "PointAndClickPlayerController.h"
#include <Utils/SaveLoadGameInstanceSubsystem.h>
#include <Utils/LevelLoaderInterface.h>
#include <Engine/LevelScriptActor.h>

DEFINE_LOG_CATEGORY(TopDownRpgMode);


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
	UE_LOGFMT(TopDownRpgMode, Log, "Pre BeginPlay() stuff...");
	bool act =  GetWorld()->GetLevelScriptActor()->Implements<ULevelLoaderInterface>();
	if (act) {
		UE_LOGFMT(TopDownRpgMode, Log, "Level {0} is impelemneting ILevelLoaderInterface, calling BindActors...", GetWorld()->GetName());
		ILevelLoaderInterface::Execute_BindActors(GetWorld()->GetLevelScriptActor());
	}

	USaveLoadGameInstanceSubsystem* saveload_handler = GetWorld()->GetGameInstance()->GetSubsystem<USaveLoadGameInstanceSubsystem>();

	if (saveload_handler) {
		saveload_handler->FinishSaveLoading(); //TODO logic for loading screens
	}

	Super::BeginPlay();

	saveload_handler->PostBeginPlay();
}
