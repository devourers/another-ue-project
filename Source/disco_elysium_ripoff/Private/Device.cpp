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

	LogicComponent = CreateDefaultSubobject<ULogicComponent>(TEXT("Logic Component"));
}

void ADevice::ToggleHighlight(bool to_toggle) {
	if (GetLogicComponent()->IsInteractionActive())
		Mesh->SetRenderCustomDepth(to_toggle);
}

void ADevice::CloseUI() {
	DeviceUI->SignalDelegate.RemoveAll(this);
	DeviceUI->RemoveFromParent();
	DeviceUI = nullptr;
}

void ADevice::InternalInteract(AActor* other_actor) {
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
	Interact(other_actor);
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
	if (protag_) {
		d_signal.PlayerPtr = protag_;
		d_signal.DeviceType = DeviceConfig.DeviceType;
		if (signal.SignalType == EDST_CodepadCorrectCode) {
			d_signal.bSuccess = true;
		}
		else {
			d_signal.bSuccess = false;
			protag_->UpdateLog(FString("Wrong code."));
		}
		OnSignalSent.Broadcast(d_signal);
	}
}

ULogicComponent* ADevice::GetLogicComponent()
{
	return LogicComponent;
}

UMainGameInstanceSubsystem* ADevice::GetHandler() {
	return handler_;
}

AProtagClass* ADevice::GetProtag() {
	return protag_;
}

void ADevice::BindProtag(AActor* other_actor) {
	protag_ = Cast<AProtagClass>(other_actor);
}