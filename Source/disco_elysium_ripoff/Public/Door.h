// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Interactable.h"
#include "../disco_elysium_ripoff.h"
#include "Components/SphereComponent.h"
#include "Components/TimelineComponent.h"
#include "Navigation/NavLinkProxy.h"
#include "Device.h"

#include "GameFramework/Actor.h"
#include "Door.generated.h"

UENUM(BlueprintType)
enum EUnlockType {
	eUT_NotLocked = 0 UMETA(DisplayName = "Not locked"),
	eUT_Key = 1 UMETA(DisplayName = "Key"),
	eUT_Device = 2 UMETA(DisplayName = "Device")
};

USTRUCT(BlueprintType)
struct FLockInfo {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EUnlockType> UnlockType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName RequiredKeyName; //also adds "WorldName_" as a prefix for easier use

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ADevice* Device; //should be castable to device/interactable
};

UCLASS()
class DISCO_ELYSIUM_RIPOFF_API ADoor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ToggleHighlight(bool to_toggle) override;

	virtual void InternalInteract(AActor* other_actor) override;

	virtual void OnCursorOver(UPrimitiveComponent* component) override;

	virtual void OnCursorEnd(UPrimitiveComponent* component) override;

	virtual void OnInteractableAsDestinationReached(AActor* other_actor) override;

	virtual void OnInteractableSelectedAsDestination() override;

	virtual USphereComponent* GetInteractionHitbox() override;

	virtual ULogicComponent* GetLogicComponent() override;

	virtual UMainGameInstanceSubsystem* GetHandler() override;

	virtual AProtagClass* GetProtag() override;

	virtual void BindProtag(AActor* other_actor) override;

	UFUNCTION()
	void OpenDoor(float Value);

	UFUNCTION()
	void UnlockDoor(AActor* other_actor);

	UFUNCTION()
	void ImplUnlock(AActor* other_actor);

	UFUNCTION()
	void OnSignalRecieved(const FDeviceSignal& signal);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* DoorFrameMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	USphereComponent* InteractionHitbox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Logic, meta = (AllowPrivateAccess = "true"))
	ULogicComponent* LogicComponent;

	UPROPERTY()
	AProtagClass* protag_;

	UPROPERTY()
	UMainGameInstanceSubsystem* handler_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	UCurveFloat* OpeningCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Navigation, meta = (AllowPrivateAccess = "true"))
	ANavLinkProxy* NavLink;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Logic, meta = (AllowPrivateAccess = true))
	bool bIsDoorLocked = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Logic, meta = (AllowPrivateAccess = true))
	FLockInfo LockInfo;

private:
	FTimeline OpeningTimeline;
	bool bIsDoorClosed = true;
	float DoorOpeningAngle = 90.0f;
};
