// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveItem.h"
#include "Misc/Paths.h"
#include "../ProtagClass.h"
#include "../MainGameInstanceSubsystem.h"

// Sets default values
AInteractiveItem::AInteractiveItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	Mesh->OnBeginCursorOver.AddDynamic(this, &AInteractiveItem::OnCursorOver);
	Mesh->OnEndCursorOver.AddDynamic(this, &AInteractiveItem::OnCursorEnd);
	Mesh->SetRenderCustomDepth(false);

	if (Type == EItemType::eIT_Pickable) {
		Mesh->SetCustomDepthStencilValue(STENCIL_PICKABLE_ITEM);
	}
	else if (Type == EItemType::eIT_Flair) {
		Mesh->SetCustomDepthStencilValue(STENCIL_FLAIR_ITEM);
	}

	InteractionHitbox = CreateDefaultSubobject<USphereComponent>(TEXT("Interaction Collision"));
	InteractionHitbox->SetCanEverAffectNavigation(false);
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

	if (Type == EItemType::eIT_Pickable) {
		Mesh->SetCustomDepthStencilValue(STENCIL_PICKABLE_ITEM);
	}
	else if (Type == EItemType::eIT_Flair) {
		Mesh->SetCustomDepthStencilValue(STENCIL_FLAIR_ITEM);
	}
	
	FString RootDir = FPaths::Combine(FPaths::ProjectContentDir(), *FString("Configs/Levels"));
	LoreEntryPath = FPaths::Combine(RootDir, GetWorld()->GetFName().ToString() + "/Lore/" + LoaderName.ToString() + ".json");
	InventoryEntryPath = FPaths::Combine(RootDir, GetWorld()->GetFName().ToString() + "/Inventory/" + LoaderName.ToString() + ".json");

	LoreEntry = NewObject<ULoreEntry>(this, TEXT("Lore Entry"));
	if (FPaths::FileExists(LoreEntryPath)) {
		LoreEntry->LoadFromJson(LoreEntryPath);
	}

	InventoryEntry = NewObject<UInventoryEntry>(this, TEXT("Inventory Entry"));
	if (FPaths::FileExists(InventoryEntryPath)) {
		InventoryEntry->LoadFromJson(InventoryEntryPath);
	}
}

// Called every frame
void AInteractiveItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AInteractiveItem::ToggleHighlight(bool to_toggle) {
	Mesh->SetRenderCustomDepth(to_toggle);
}


void AInteractiveItem::Interact(AActor* other_actor) {
	if (Type == EItemType::eIT_Pickable) {
		if (InventoryEntry) {
			UMainGameInstanceSubsystem* handler = GetGameInstance()->GetSubsystem<UMainGameInstanceSubsystem>();
			if (handler) {
				UInventoryEntry* entry = NewObject<UInventoryEntry>();
				entry->SetTitle(InventoryEntry->GetTitle());
				entry->SetKeywords(InventoryEntry->GetKeywords());
				entry->SetDescription(InventoryEntry->GetDescription());
				entry->SetImages(InventoryEntry->GetImages());
				FName entry_name = FName(GetWorld()->GetName() + "_" + LoaderName.ToString());
				handler->AddItemToInventory(entry_name, entry);
				AProtagClass* protag = Cast<AProtagClass>(other_actor);
				if (protag) {
					FString log_entry = FString("Item picked up: ") + DisplayedName.ToString();
					protag->UpdateLog(log_entry);
				}
				Destroy();
			}
		}
	}
	else if (Type == EItemType::eIT_Flair) {

	}
}


void AInteractiveItem::OnCursorOver(UPrimitiveComponent* component) {
	ToggleHighlight(true);
}


void AInteractiveItem::OnCursorEnd(UPrimitiveComponent* component) {
	if (!IsSelectedAsDestination())
		ToggleHighlight(false);
}


void AInteractiveItem::OnInteractableSelectedAsDestination() {
	SetIsSelectedAsDestination(true);
	Mesh->SetRenderCustomDepth(true);
}


void AInteractiveItem::OnInteractableAsDestinationReached(AActor* other_actor) {
	SetIsSelectedAsDestination(false);
	Mesh->SetRenderCustomDepth(false);
	if (InteractionHitbox->IsOverlappingActor(other_actor)) {
		Interact(other_actor);
	}
}

USphereComponent* AInteractiveItem::GetInteractionHitbox() {
	return InteractionHitbox;
}