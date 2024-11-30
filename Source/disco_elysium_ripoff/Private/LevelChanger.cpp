// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelChanger.h"

// Sets default values
ALevelChanger::ALevelChanger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	Mesh->OnBeginCursorOver.AddDynamic(this, &ALevelChanger::OnCursorOver);
	Mesh->OnEndCursorOver.AddDynamic(this, &ALevelChanger::OnCursorEnd);
	Mesh->SetRenderCustomDepth(false);
	Mesh->SetCustomDepthStencilValue(STENCIL_DEVICE);

	InteractionHitbox = CreateDefaultSubobject<USphereComponent>(TEXT("Interaction Collision"));
	InteractionHitbox->SetCanEverAffectNavigation(false);
	InteractionHitbox->SetupAttachment(Mesh);
	InteractionHitbox->SetGenerateOverlapEvents(true);
	InteractionHitbox->SetCollisionProfileName("NoCollision");
	InteractionHitbox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionHitbox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

}

// Called when the game starts or when spawned
void ALevelChanger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelChanger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelChanger::ToggleHighlight(bool to_toggle) {
	Mesh->SetRenderCustomDepth(to_toggle);
}

void ALevelChanger::Interact(AActor* other_actor) {
	if (Configuration.Type == ELevelChangerType::ELCT_InLevelTeleporter) {
		if (Configuration.OtherTeleport) {
			bool success = other_actor->TeleportTo(Configuration.OtherTeleport->GetInteractionHitbox()->GetComponentLocation(), other_actor->GetActorRotation());
			if (success) {
				GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString("Teleported"));
			}
			else {
				GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString("Not teleported"));
			}
		}
	}
	else {
		//TODO
	}
}

void ALevelChanger::OnCursorOver(UPrimitiveComponent* Component) {
	ToggleHighlight(true);
}

void ALevelChanger::OnCursorEnd(UPrimitiveComponent* Component) {
	if (!IsSelectedAsDestination())
		ToggleHighlight(false);
}

void ALevelChanger::OnInteractableAsDestinationReached(AActor* other_actor) {
	SetIsSelectedAsDestination(false);
	Mesh->SetRenderCustomDepth(false);
	Interact(other_actor);
}

void ALevelChanger::OnInteractableSelectedAsDestination() {
	SetIsSelectedAsDestination(true);
	Mesh->SetRenderCustomDepth(true);
}

USphereComponent* ALevelChanger::GetInteractionHitbox() {
	return InteractionHitbox;
}