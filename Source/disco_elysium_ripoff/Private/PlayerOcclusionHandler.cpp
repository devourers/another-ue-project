// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerOcclusionHandler.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "Kismet/GameplayStatics.h"

UPlayerOcclusionHandler::UPlayerOcclusionHandler() {
	ConstructorHelpers::FObjectFinder<UMaterialParameterCollection> objectType(TEXT("/Game/Material/Collection/MPC_OcclusionData"));
	if (objectType.Succeeded())
		collection_ = objectType.Object;
}

UPlayerOcclusionHandler::UPlayerOcclusionHandler(AActor* player) {
	player_ = player;
	ConstructorHelpers::FObjectFinder<UMaterialParameterCollection> objectType(TEXT("/Game/Material/Collection/MPC_OcclusionData"));
	if (objectType.Succeeded())
		collection_ = objectType.Object;
}

void UPlayerOcclusionHandler::BindPlayer(AActor* player) {
	player_ = player;
}

void UPlayerOcclusionHandler::SetCharacterPosition() {
	FVector2D viewport_size;
	if (GetWorld() && GetWorld()->GetGameViewport()) {
		GetWorld()->GetGameViewport()->GetViewportSize(viewport_size);
		APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		FVector player_location = player_->GetActorLocation();
		FVector2D projected_location;
		controller->ProjectWorldLocationToScreen(player_location, projected_location);
		FVector2D character_pos_relative;
		character_pos_relative.X = projected_location.X / viewport_size.X;
		character_pos_relative.Y = projected_location.Y / viewport_size.Y;
		UMaterialParameterCollectionInstance* pci = GetWorld()->GetParameterCollectionInstance(collection_);
		if (pci) {
			pci->SetVectorParameterValue(FName("CharPos"), FLinearColor(character_pos_relative.X, character_pos_relative.Y, 0));
		}
	}
}

void UPlayerOcclusionHandler::SetShouldApplyOcclusion(bool isBehindWall, bool radius_condition) {
	UMaterialParameterCollectionInstance* pci = GetWorld()->GetParameterCollectionInstance(collection_);
	if (pci) {
		pci->SetScalarParameterValue(FName("ShouldApplyOcclusion"), float(int(isBehindWall || radius_condition)));
	}
	__internal__ShouldApplyOcclusion = isBehindWall;
}

void UPlayerOcclusionHandler::SetOcclusionRadius(float DeltaTime) {

	float multiplyer = __internal__ShouldApplyOcclusion ? 1.0f : -1.0f;
	CurrentOcclusionRadius += (OcclusionRadius / FadeDuration) * DeltaTime * multiplyer;
	CurrentOcclusionRadius = FMath::Clamp(CurrentOcclusionRadius, 0.0, OcclusionRadius);

	UMaterialParameterCollectionInstance* pci = GetWorld()->GetParameterCollectionInstance(collection_);
	if (pci) {
		pci->SetScalarParameterValue(FName("Radius"), CurrentOcclusionRadius);
	}
}

float UPlayerOcclusionHandler::GetCurrentOcclusionRadius() const {
	return CurrentOcclusionRadius;
}