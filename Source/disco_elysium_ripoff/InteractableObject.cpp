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
}


void AInteractableObject::OnCursorOver(UPrimitiveComponent* Component) {
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString("OnCursorOver"));
	Mesh->SetMaterial(0, SelectedMaterial);

}


void AInteractableObject::OnCursorEnd(UPrimitiveComponent* Component) {
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString("OnCursorEnd"));
	Mesh->SetMaterial(0, UnselectedMaterial);
}