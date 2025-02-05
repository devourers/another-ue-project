// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "../Interactable.h"
#include "../disco_elysium_ripoff.h"

#include "Companion.generated.h"

class ACompanionAIController;

UCLASS()
class DISCO_ELYSIUM_RIPOFF_API ACompanion : public ACharacter, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACompanion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public: //overrides
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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnPlayerDoubleClicked(bool didDoubleClick);

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Logic, meta = (AllowPrivateAccess = "true"))
	ULogicComponent* LogicComponent;

	UPROPERTY()
	AProtagClass* protag_;

	UPROPERTY()
	UMainGameInstanceSubsystem* handler_;

	UPROPERTY()
	ACompanionAIController* controller_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	USphereComponent* InteractionHitbox;

};
