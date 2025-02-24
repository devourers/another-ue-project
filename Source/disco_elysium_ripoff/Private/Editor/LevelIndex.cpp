// Fill out your copyright notice in the Description page of Project Settings.


#include "Editor/LevelIndex.h"

void ULevelIndex::BuildIndex(const TArray<FString>& levels){
	Levels.Reset();
	Levels.Reserve(levels.Num());
	for (auto level : levels) {
		AddLevel(level);
	}
	is_initialized = true;
}

void ULevelIndex::RemoveLevel(const FString& level){
	Levels.Remove(Levels.FindId(level));
}

void ULevelIndex::AddLevel(const FString& level){
	Levels.Add(level);
}

bool ULevelIndex::HasLevel(const FString& level) {
	return Levels.Contains(level);
}

bool ULevelIndex::IsInitialised() const{
	return is_initialized;
}

const FString& ULevelIndex::GetCurrentLevel() const{
	return CurrentLevel;
}

void ULevelIndex::SetCurrentLevel(const FString& level){
	CurrentLevel = level;
	OnCurrentLevelChanged.Broadcast(CurrentLevel);
}
