// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelChanger.h"
#include "../ProtagClass.h"

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

void ALevelChanger::TeleportTimerElapsed() {
	PlayerPtr->TeleportTo(Configuration.OtherTeleport->GetInteractionHitbox()->GetComponentLocation(), PlayerPtr->GetActorRotation());
	GetWorldTimerManager().SetTimer(
		UnusedHandle, PlayerPtr, &AProtagClass::FadeOutAfterTeleport, 1.0f, false);
}

void ALevelChanger::Interact(AActor* other_actor) {
	IInteractable::Interact(other_actor);
	if (Configuration.Type == ELevelChangerType::ELCT_InLevelTeleporter) {
		if (Configuration.OtherTeleport) {
			AProtagClass* protag = Cast<AProtagClass>(other_actor);
			PlayerPtr = protag;
			protag->FadeCamera(true);
			GetWorldTimerManager().SetTimer(
				UnusedHandle, this, &ALevelChanger::TeleportTimerElapsed, 1.0f, false);
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString("Teleported"));
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

ULogicComponent* ALevelChanger::GetLogicComponent()
{
	return LogicComponent;
}
