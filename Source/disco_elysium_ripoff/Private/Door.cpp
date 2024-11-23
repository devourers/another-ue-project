// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "../MainGameInstanceSubsystem.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorFrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	DoorFrameMesh->SetupAttachment(RootComponent);

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	DoorMesh->SetupAttachment(DoorFrameMesh);

	if (!bIsDoorLocked) {
		DoorFrameMesh->SetCustomDepthStencilValue(STENCIL_UNLOCKED_DOOR);
		DoorFrameMesh->SetRenderCustomDepth(false);

		DoorMesh->SetCustomDepthStencilValue(STENCIL_UNLOCKED_DOOR);
		DoorMesh->SetRenderCustomDepth(false);
	}
	else {
		DoorFrameMesh->SetCustomDepthStencilValue(STENCIL_LOCKED_DOOR);
		DoorFrameMesh->SetRenderCustomDepth(false);

		DoorMesh->SetCustomDepthStencilValue(STENCIL_LOCKED_DOOR);
		DoorMesh->SetRenderCustomDepth(false);
	}

	DoorMesh->OnBeginCursorOver.AddDynamic(this, &ADoor::OnCursorOver);
	DoorMesh->OnEndCursorOver.AddDynamic(this, &ADoor::OnCursorEnd);

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

	if (!bIsDoorLocked) {
		DoorFrameMesh->SetCustomDepthStencilValue(STENCIL_UNLOCKED_DOOR);
		DoorFrameMesh->SetRenderCustomDepth(false);

		DoorMesh->SetCustomDepthStencilValue(STENCIL_UNLOCKED_DOOR);
		DoorMesh->SetRenderCustomDepth(false);
	}
	else {
		DoorFrameMesh->SetCustomDepthStencilValue(STENCIL_LOCKED_DOOR);
		DoorFrameMesh->SetRenderCustomDepth(false);

		DoorMesh->SetCustomDepthStencilValue(STENCIL_LOCKED_DOOR);
		DoorMesh->SetRenderCustomDepth(false);
	}

	if (OpeningCurve) {
		FOnTimelineFloat TimeLineProgress;
		TimeLineProgress.BindDynamic(this, &ADoor::OpenDoor);
		OpeningTimeline.AddInterpFloat(OpeningCurve, TimeLineProgress);
	}
	if (NavLink) {
		NavLink->SetSmartLinkEnabled(false);
		NavLink->CopyEndPointsFromSimpleLinkToSmartLink();
		NavLink->PointLinks.Empty();
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

void ADoor::ImplUnlock() {
	bIsDoorLocked = false;
	DoorFrameMesh->SetCustomDepthStencilValue(STENCIL_UNLOCKED_DOOR);
	DoorMesh->SetCustomDepthStencilValue(STENCIL_UNLOCKED_DOOR);
}

void ADoor::UnlockDoor() {
	//logic goes here....
	UMainGameInstanceSubsystem* handler = GetGameInstance()->GetSubsystem<UMainGameInstanceSubsystem>();
	if (handler) {
		if (LockInfo.UnlockType == EUnlockType::eUT_NotLocked) {
			ImplUnlock();
		}
		if (LockInfo.UnlockType == EUnlockType::eUT_Key) {
			FName full_key_name = FName(GetWorld()->GetFName().ToString() + "_" + LockInfo.RequiredKeyName.ToString());
			if (handler->CheckInventoryForItem(full_key_name)) {
				GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString("Unlocked with key " + full_key_name.ToString()));
				ImplUnlock();
			}
			else {
				GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString("You don't have the key"));
			}
		}
	}
}

void ADoor::Interact() {
	if (!bIsDoorLocked) {
		if (bIsDoorClosed) {
			OpeningTimeline.Play();
			if (NavLink)
				NavLink->SetSmartLinkEnabled(true);
		}
		else {
			OpeningTimeline.Reverse();
			if (NavLink)
				NavLink->SetSmartLinkEnabled(false);
		}
		bIsDoorClosed = !bIsDoorClosed;
	}
	else {
		UnlockDoor();
	}
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
	Interact();
}

void ADoor::OnInteractableSelectedAsDestination() {
	SetIsSelectedAsDestination(true);
	DoorMesh->SetRenderCustomDepth(true);
	DoorFrameMesh->SetRenderCustomDepth(true);
}

USphereComponent* ADoor::GetInteractionHitbox() {
	return InteractionHitbox;
}