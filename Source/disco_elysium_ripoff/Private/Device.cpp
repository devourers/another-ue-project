// Fill out your copyright notice in the Description page of Project Settings.


#include "Device.h"
#include "../PointAndClickPlayerController.h"
#include "../ProtagClass.h"

// Sets default values
ADevice::ADevice()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	Mesh->OnBeginCursorOver.AddDynamic(this, &ADevice::OnCursorOver);
	Mesh->OnEndCursorOver.AddDynamic(this, &ADevice::OnCursorEnd);
	Mesh->SetRenderCustomDepth(false);
	Mesh->SetCustomDepthStencilValue(STENCIL_DEVICE);

	InteractionHitbox = CreateDefaultSubobject<USphereComponent>(TEXT("Interaction Collision"));
	InteractionHitbox->SetCanEverAffectNavigation(false);
	InteractionHitbox->SetupAttachment(Mesh);
	InteractionHitbox->SetGenerateOverlapEvents(true);
	InteractionHitbox->SetCollisionProfileName("NoCollision");
	InteractionHitbox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionHitbox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	DeviceUIClass = nullptr;
	DeviceUI = nullptr;
}

void ADevice::ToggleHighlight(bool to_toggle) {
	Mesh->SetRenderCustomDepth(to_toggle);
}

void ADevice::CloseUI() {
	DeviceUI->RemoveFromViewport();
	DeviceUI = nullptr;
}

void ADevice::Interact(AActor* other_actor) {
	if (DeviceConfig.DeviceType == EDeviceType::eDT_Lockpad) {
		if (DeviceUIClass && !DeviceUI) {
			AProtagClass* protag = Cast<AProtagClass>(other_actor);
			APointAndClickPlayerController* PCC = protag->GetController<APointAndClickPlayerController>();
			DeviceUI = CreateWidget<UBaseDeviceUI>(PCC, DeviceUIClass);
			DeviceUI->BindDevice(this);
			DeviceUI->SetupUIFromDeviceConfig(DeviceConfig);
			DeviceUI->SignalDelegate.AddUniqueDynamic(this, &ADevice::OnSignalRecieved);
			DeviceUI->AddToPlayerScreen();
			DeviceUI->SetFocus();
		}
	}
}

void ADevice::OnCursorOver(UPrimitiveComponent* Component) {
	ToggleHighlight(true);
}

void ADevice::OnCursorEnd(UPrimitiveComponent* Component) {
	if (!IsSelectedAsDestination())
		ToggleHighlight(false);
}

void ADevice::OnInteractableAsDestinationReached(AActor* other_actor) {
	SetIsSelectedAsDestination(false);
	Mesh->SetRenderCustomDepth(false);
	//if (InteractionHitbox->IsOverlappingActor(other_actor)) {
	Interact(other_actor);
	//}
}

void ADevice::OnInteractableSelectedAsDestination() {
	SetIsSelectedAsDestination(true);
	Mesh->SetRenderCustomDepth(true);
}

USphereComponent* ADevice::GetInteractionHitbox() {
	return InteractionHitbox;
}

// Called when the game starts or when spawned
void ADevice::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADevice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Mesh->SetCustomDepthStencilValue(STENCIL_DEVICE);
	//TODO: load devices
}

void ADevice::OnSignalRecieved(const FDeviceUISignal& signal) {
	FDeviceSignal d_signal;
	d_signal.DeviceType = DeviceConfig.DeviceType;
	if (signal.SignalType == EDST_CodepadCorrectCode) {
		d_signal.bSuccess = true;
	}
	else {
		d_signal.bSuccess = false;
	}
	OnSignalSent.Broadcast(d_signal);
}