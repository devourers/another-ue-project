// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/ActorBindGameInstanceSubsystem.h"

DEFINE_LOG_CATEGORY(ActorBindGameInstanceSubsystem);

void UActorBindGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection){
	Super::Initialize(Collection);
	UE_LOGFMT(ActorBindGameInstanceSubsystem, Log, "Initialised actor bind subsystem");
}

void UActorBindGameInstanceSubsystem::Deinitialize(){
	Super::Deinitialize();
}
