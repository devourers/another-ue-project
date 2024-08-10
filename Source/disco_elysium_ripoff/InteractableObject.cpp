// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObject.h"


AInteractableObject::AInteractableObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	Mesh->OnBeginCursorOver.AddDynamic(this, &AInteractableObject::OnCursorOver);
	Mesh->OnEndCursorOver.AddDynamic(this, &AInteractableObject::OnCursorEnd);
	Mesh->SetMaterial(0, UnselectedMaterial);
	Mesh->SetCanEverAffectNavigation(false);

	tooltip = CreateDefaultSubobject<UHoverWidgetComponent>(TEXT("Tooltip Widget"));
	tooltip->SetVisibility(false);
	tooltip->SetupAttachment(GetRootComponent());
}

void AInteractableObject::BeginPlay() {
	Super::BeginPlay();
	tooltip->SetVisibility(false);
	tooltip->SetHeader(GetName());
	tooltip->SetDescription(GetDescription());
}


void AInteractableObject::OnCursorOver(UPrimitiveComponent* Component) {
	if (!IsSelectedAsDestination()) {
		Mesh->SetMaterial(0, SelectedMaterial);
		tooltip->SetVisibility(true);
	}

}


void AInteractableObject::OnCursorEnd(UPrimitiveComponent* Component) {
	if (!IsSelectedAsDestination()) {
		Mesh->SetMaterial(0, UnselectedMaterial);
		tooltip->SetVisibility(false);
	}
}

void AInteractableObject::OnActorSelectedAsDestination() {
	SetIsSelectedAsDestination(true);
	tooltip->SetVisibility(true);
	Mesh->SetMaterial(0, SelectedMaterial);
}

void AInteractableObject::OnActorAsDestinationReached() {
	SetIsSelectedAsDestination(false);
	tooltip->SetVisibility(false);
	Mesh->SetMaterial(0, UnselectedMaterial);
}