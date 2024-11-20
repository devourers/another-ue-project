// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveItem.h"

// Sets default values
AInteractiveItem::AInteractiveItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	ItemMaterialInstance = UMaterialInstanceDynamic::Create(ItemMaterial, Mesh);

	Mesh->OnBeginCursorOver.AddDynamic(this, &AInteractiveItem::OnCursorOver);
	Mesh->OnEndCursorOver.AddDynamic(this, &AInteractiveItem::OnCursorEnd);
	Mesh->SetRenderCustomDepth(true);

	if (Type = EItemType::eIT_Pickable) {
		Mesh->SetCustomDepthStencilValue(STENCIL_PICKABLE_ITEM);
	}
	else if (Type = EItemType::eIT_Flair) {
		Mesh->SetCustomDepthStencilValue(STENCIL_FLAIR_ITEM);
	}

	Mesh->SetMaterial(0, ItemMaterialInstance);
	Mesh->SetCanEverAffectNavigation(false);

	InteractionHitbox = CreateDefaultSubobject<USphereComponent>(TEXT("Interaction Collision"));
	InteractionHitbox->SetupAttachment(Mesh);
	InteractionHitbox->SetGenerateOverlapEvents(true);
	InteractionHitbox->SetCollisionProfileName("NoCollision");
	InteractionHitbox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionHitbox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

}

// Called when the game starts or when spawned
void AInteractiveItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractiveItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AInteractiveItem::ToggleHighlight(bool to_toggle) {
	Mesh->SetRenderCustomDepth(to_toggle);
}


void AInteractiveItem::Interact() {
	if (Type = EItemType::eIT_Pickable) {

	}
	else if (Type = EItemType::eIT_Flair) {

	}
}


void AInteractiveItem::OnCursorOver(UPrimitiveComponent* component) {
	ToggleHighlight(true);
}


void AInteractiveItem::OnCursorEnd(UPrimitiveComponent* component) {
	ToggleHighlight(false);
}


void AInteractiveItem::OnActorSelectedAsDestination() {

}


void AInteractiveItem::OnActorAsDestinationReached(AActor* other_actor) {

}