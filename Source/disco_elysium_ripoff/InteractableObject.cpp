// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObject.h"
#include "MainGameInstanceSubsystem.h"

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

void AInteractableObject::OnActorAsDestinationReached(AActor* other_actor) {
	SetIsSelectedAsDestination(false);
	tooltip->SetVisibility(false);
	Mesh->SetMaterial(0, UnselectedMaterial);
	float a = GetDistanceTo(other_actor);
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::SanitizeFloat(a));
	if (a < 105.0f)
	{
		UMainGameInstanceSubsystem* handler =  GetGameInstance()->GetSubsystem<UMainGameInstanceSubsystem>();
		if (handler) {
			FName name(this->GetName());
			FInventoryEntry entry;
			entry.Name = name;
			entry.Description = this->GetDescription();
			handler->AddItemToInventory(name, entry);
			Destroy();
		}
	}
}