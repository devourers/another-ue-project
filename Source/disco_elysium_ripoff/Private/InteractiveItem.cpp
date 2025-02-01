// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveItem.h"
#include "Misc/Paths.h"
#include "../ProtagClass.h"
#include "../PointAndClickPlayerController.h"
#include "Dialogue/DialogueUI.h"
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

	LogicComponent = CreateDefaultSubobject<ULogicComponent>(TEXT("Logic Component"));
}

// Called when the game starts or when spawned
void AInteractiveItem::BeginPlay()
{
	Super::BeginPlay();

	handler_ = GetGameInstance()->GetSubsystem<UMainGameInstanceSubsystem>();

	if (Type == EItemType::eIT_Pickable) {
		Mesh->SetCustomDepthStencilValue(STENCIL_PICKABLE_ITEM);
	}
	else if (Type == EItemType::eIT_Flair) {
		Mesh->SetCustomDepthStencilValue(STENCIL_FLAIR_ITEM);
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

void AInteractiveItem::InternalInteract(AActor* other_actor) {
	if (Type == EItemType::eIT_Pickable) {
		Destroy();
	}
	else if (Type == EItemType::eIT_Flair) {
		//TODO
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

ULogicComponent* AInteractiveItem::GetLogicComponent(){
	return LogicComponent;
}

UMainGameInstanceSubsystem* AInteractiveItem::GetHandler(){
	return handler_;
}

AProtagClass* AInteractiveItem::GetProtag(){
	return protag_;
}

void AInteractiveItem::BindProtag(AActor* other_actor){
	protag_ = Cast<AProtagClass>(other_actor);
}
