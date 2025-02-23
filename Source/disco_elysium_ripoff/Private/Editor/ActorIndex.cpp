// Fill out your copyright notice in the Description page of Project Settings.


#include "Editor/ActorIndex.h"

void UActorIndex::BuildIndex(const TArray<FString>& actors){
	Actors.Reset();
	Actors.Reserve(actors.Num());
	for (auto actor : actors) {
		AddActor(actor);
	}
	is_initialized = true;
}

void UActorIndex::RemoveActor(const FString& actor){
	return Actors.Remove(Actors.FindId(actor));
}

void UActorIndex::AddActor(const FString& actor){
	Actors.Add(actor);
}

bool UActorIndex::HasActor(const FString& actor)
{
	return Actors.Contains(actor);
}

bool UActorIndex::IsInitialised() const
{
	return is_initialized;
}
