// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "../disco_elysium_ripoff.h"

#include "Interactable.h"
#include "LoreEntry.h"
#include "BaseDeviceUI.h"

#include "Device.generated.h"

UENUM(BlueprintType)
enum EDeviceType {
	eDT_Lockpad = 0 UMETA(DisplayName = "Lockpad"),
	eDT_Computer = 1 UMETA(DisplayName = "Computer")
};

USTRUCT(BlueprintType)
struct FDeviceConfig {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EDeviceType> DeviceType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CodepadCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxCodepadCodeLength; //to reset UI

	//this will be a big struct probs...
	//may be use class with interface?
};


UCLASS()
class DISCO_ELYSIUM_RIPOFF_API ADevice : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADevice();

	virtual void ToggleHighlight(bool to_toggle) override;

	virtual void Interact(AActor* other_actor) override;

	virtual void OnCursorOver(UPrimitiveComponent* Component) override;

	virtual void OnCursorEnd(UPrimitiveComponent* Component) override;

	virtual void OnInteractableAsDestinationReached(AActor* other_actor) override;

	virtual void OnInteractableSelectedAsDestination() override;

	virtual USphereComponent* GetInteractionHitbox() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	FName DisplayedName; //name for gameplay purposes

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Loading, meta = (AllowPrivateAccess = "true"))
	FName LoaderName; //name for loading items from configs 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	FDeviceConfig DeviceConfig;

	UPROPERTY()
	ULoreEntry* LoreEntry; //Associated with item lore entry. Loads from JSON

	UPROPERTY(VisibleAnywhere, Category = Loading)
	FString LoreEntryPath; //sets automatically in constructor via level ID and object name

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	USphereComponent* InteractionHitbox;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UBaseDeviceUI> DeviceUIClass;

	UPROPERTY()
	class UBaseDeviceUI* DeviceUI;

};
