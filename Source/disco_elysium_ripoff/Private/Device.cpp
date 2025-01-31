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
	DeviceUI->RemoveFromParent();
	DeviceUI = nullptr;
}

void ADevice::Interact(AActor* other_actor) {
	IInteractable::Interact(other_actor);
	PlayerPtr = Cast<AProtagClass>(other_actor);
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
	if (InteractionHitbox->IsOverlappingActor(other_actor)) {
		Interact(other_actor);
	}
}

void ADevice::OnInteractableSelectedAsDestination() {
	SetIsSelectedAsDestination(true);
	Mesh->SetRenderCustomDepth(true);
}

USphereComponent* ADevice::GetInteractionHitbox() {
	return InteractionHitbox;
}

ULogicComponent* ADevice::GetLogicComponent()
{
	return LogicComponent;
}

// Called when the game starts or when spawned
void ADevice::BeginPlay()
{
	Super::BeginPlay();

	Mesh->SetCustomDepthStencilValue(STENCIL_DEVICE);
}

// Called every frame
void ADevice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//TODO: load devices
}

void ADevice::OnSignalRecieved(const FDeviceUISignal& signal) {
	FDeviceSignal d_signal;
	d_signal.PlayerPtr = PlayerPtr;
	d_signal.DeviceType = DeviceConfig.DeviceType;
	if (signal.SignalType == EDST_CodepadCorrectCode) {
		d_signal.bSuccess = true;
	}
	else {
		d_signal.bSuccess = false;
		PlayerPtr->UpdateLog(FString("Wrong code."));
	}
	OnSignalSent.Broadcast(d_signal);
}