// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorFrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	DoorFrameMesh->SetupAttachment(RootComponent);

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	DoorMesh->SetupAttachment(DoorFrameMesh);

	DoorFrameMesh->SetCustomDepthStencilValue(STENCIL_UNLOCKED_DOOR);
	DoorFrameMesh->SetRenderCustomDepth(false);

	DoorMesh->SetCustomDepthStencilValue(STENCIL_UNLOCKED_DOOR);
	DoorMesh->SetRenderCustomDepth(false);

	InteractionHitbox = CreateDefaultSubobject<USphereComponent>(TEXT("Interaction Collision"));
	InteractionHitbox->SetupAttachment(DoorFrameMesh);
	InteractionHitbox->SetGenerateOverlapEvents(true);
	InteractionHitbox->SetCollisionProfileName("NoCollision");
	InteractionHitbox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionHitbox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	OpeningCurve = CreateDefaultSubobject<UCurveFloat>(TEXT("Opening Curve"));
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	if (OpeningCurve) {
		FOnTimelineFloat TimeLineProgress;
		TimeLineProgress.BindDynamic(this, &ADoor::OpenDoor);
		OpeningTimeline.AddInterpFloat(OpeningCurve, TimeLineProgress);
	}
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	OpeningTimeline.TickTimeline(DeltaTime);
}


void ADoor::ToggleHighlight(bool to_toggle) {
	DoorMesh->SetRenderCustomDepth(to_toggle);
	DoorFrameMesh->SetRenderCustomDepth(to_toggle);
}

void ADoor::OpenDoor(float Value) {
	FRotator Rot = FRotator(0.0f, DoorOpeningAngle * Value, 0.0f);

	DoorMesh->SetRelativeRotation(Rot);
}

void ADoor::Interact() {
	if (bIsDoorClosed) {
		OpeningTimeline.Play();
	}
	else {
		OpeningTimeline.Reverse();
	}
	bIsDoorClosed = !bIsDoorClosed;
}

void ADoor::OnCursorOver(UPrimitiveComponent* component) {
	ToggleHighlight(true);
}

void ADoor::OnCursorEnd(UPrimitiveComponent* component) {
	ToggleHighlight(false);
}

void ADoor::OnInteractableAsDestinationReached(AActor* other_actor) {
	SetIsSelectedAsDestination(false);
	DoorMesh->SetRenderCustomDepth(false);
	DoorFrameMesh->SetRenderCustomDepth(false);
	//if (InteractionHitbox->IsOverlappingActor(other_actor)) {
		Interact();
	//}
}

void ADoor::OnInteractableSelectedAsDestination() {
	SetIsSelectedAsDestination(true);
	DoorMesh->SetRenderCustomDepth(true);
	DoorFrameMesh->SetRenderCustomDepth(true);
}

USphereComponent* ADoor::GetInteractionHitbox() {
	return InteractionHitbox;
}