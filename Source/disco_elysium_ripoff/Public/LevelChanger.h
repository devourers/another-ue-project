// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "../disco_elysium_ripoff.h"
#include "LevelChanger.generated.h"

class ALevelChanger;

UENUM()
enum ELevelChangerType {
	ELCT_InLevelTeleporter = 0 UMETA(DisplayName = "In Level Teleporter"),
	ELCT_LevelExit = 1 UMETA(DisplayName = "Level exit")
};

USTRUCT(BlueprintType)
struct FLevelChangerConfig {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = General)
	TEnumAsByte<ELevelChangerType> Type;

	UPROPERTY(EditAnywhere, Category = General, meta = (EditCondition = "Type == ELevelChangerType::ELCT_InLevelTeleporter", EditConditionHides))
	class ALevelChanger* OtherTeleport;

	UPROPERTY(EditAnywhere, Category = General, meta = (EditCondition = "Type == ELevelChangerType::ELCT_LevelExit", EditConditionHides))
	FString LevelPath;
};

UCLASS()
class DISCO_ELYSIUM_RIPOFF_API ALevelChanger : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelChanger();

	virtual void ToggleHighlight(bool to_toggle) override;

	virtual void InternalInteract(AActor* other_actor) override;

	virtual void OnCursorOver(UPrimitiveComponent* Component) override;

	virtual void OnCursorEnd(UPrimitiveComponent* Component) override;

	virtual void OnInteractableAsDestinationReached(AActor* other_actor) override;

	virtual void OnInteractableSelectedAsDestination() override;

	virtual USphereComponent* GetInteractionHitbox() override;

	virtual ULogicComponent* GetLogicComponent() override;

	virtual UMainGameInstanceSubsystem* GetHandler() override;

	virtual AProtagClass* GetProtag() override;

	virtual void BindProtag(AActor* other_actor) override;

	UFUNCTION()
	void TeleportTimerElapsed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	FName DisplayedName; //name for gameplay purposes

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Logic, meta = (AllowPrivateAccess = "true"))
	ULogicComponent* LogicComponent;

	UPROPERTY()
	AProtagClass* protag_;

	UPROPERTY()
	UMainGameInstanceSubsystem* handler_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Loading, meta = (AllowPrivateAccess = "true"))
	FName LoaderName; //name for loading items from configs 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	USphereComponent* InteractionHitbox;

	UPROPERTY()
	class UBaseDeviceUI* ExitLocationUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = General, meta = (AllowPrivateAccess = "true"))
	FLevelChangerConfig Configuration;

	UPROPERTY()
	FTimerHandle UnusedHandle;

};
