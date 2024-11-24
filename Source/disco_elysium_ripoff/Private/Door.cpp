// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "../MainGameInstanceSubsystem.h"
#include "../ProtagClass.h"
#include "NavLinkCustomComponent.h"

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

void ADoor::ImplUnlock(AActor* other_actor) {
	bIsDoorLocked = false;
	DoorFrameMesh->SetCustomDepthStencilValue(STENCIL_UNLOCKED_DOOR);
	DoorMesh->SetCustomDepthStencilValue(STENCIL_UNLOCKED_DOOR);
	AProtagClass* protag = Cast<AProtagClass>(other_actor);
	if (protag) {
		FString log_entry = FString("Door unlocked.");
		protag->UpdateLog(log_entry);
	}
}

void ADoor::UnlockDoor(AActor* other_actor) {
	UMainGameInstanceSubsystem* handler = GetGameInstance()->GetSubsystem<UMainGameInstanceSubsystem>();
	if (handler) {
		if (LockInfo.UnlockType == EUnlockType::eUT_NotLocked) {
			ImplUnlock(other_actor);
		}
		if (LockInfo.UnlockType == EUnlockType::eUT_Key) {
			FName full_key_name = FName(GetWorld()->GetFName().ToString() + "_" + LockInfo.RequiredKeyName.ToString());
			if (handler->CheckInventoryForItem(full_key_name)) {
				GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString("Unlocked with key " + full_key_name.ToString()));
				ImplUnlock(other_actor);
			}
			else {
				AProtagClass* protag = Cast<AProtagClass>(other_actor);
				if (protag) {
					FString log_entry = FString("You don't have the key.");
					protag->UpdateLog(log_entry);
				}
			}
		}
	}
}

void ADoor::Interact(AActor* other_actor) {
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
		UnlockDoor(other_actor);
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
	Interact(other_actor);
}

void ADoor::OnInteractableSelectedAsDestination() {
	SetIsSelectedAsDestination(true);
	DoorMesh->SetRenderCustomDepth(true);
	DoorFrameMesh->SetRenderCustomDepth(true);
}

USphereComponent* ADoor::GetInteractionHitbox() {
	return InteractionHitbox;
}