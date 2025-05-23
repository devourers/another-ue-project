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

	LogicComponent = CreateDefaultSubobject<ULogicComponent>(TEXT("Logic Component"));
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
	if (GetLogicComponent()->IsInteractionActive())
		Mesh->SetRenderCustomDepth(to_toggle);
}

void ALevelChanger::TeleportTimerElapsed() {
	if (protag_) {
		protag_->TeleportTo(Configuration.OtherTeleport->GetInteractionHitbox()->GetComponentLocation(), protag_->GetActorRotation());
		protag_->PlayerTeleported.Broadcast(Configuration.OtherTeleport->GetInteractionHitbox()->GetComponentLocation());
		GetWorldTimerManager().SetTimer(
			UnusedHandle, protag_, &AProtagClass::FadeOutAfterTeleport, 1.0f, false);
	}
}

void ALevelChanger::InternalInteract(AActor* other_actor){
	if (Configuration.Type == ELevelChangerType::ELCT_InLevelTeleporter) {
		if (Configuration.OtherTeleport) {
			protag_->DisableProtagInput();
			protag_->FadeCamera(true);
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

UMainGameInstanceSubsystem* ALevelChanger::GetHandler() {
	return handler_;
}

AProtagClass* ALevelChanger::GetProtag() {
	return protag_;
}

void ALevelChanger::BindProtag(AActor* other_actor) {
	protag_ = Cast<AProtagClass>(other_actor);
}