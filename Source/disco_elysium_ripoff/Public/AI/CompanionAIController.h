// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "CompanionAIController.generated.h"

class ACompanion;
class AProtagClass;
/**
 * 
 */
UCLASS()
class DISCO_ELYSIUM_RIPOFF_API ACompanionAIController : public AAIController
{

	GENERATED_BODY()

public:
	ACompanionAIController();

	virtual void OnPossess(APawn* pawn) override;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPlayerTargetLocationUpdated(const FVector& target_location);

	UFUNCTION()
	void OnPlayerTeleported(const FVector& teleport_location);


private:
	UPROPERTY()
	ACompanion* companion_;

	UPROPERTY()
	AProtagClass* protag_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
	UBehaviorTreeComponent* BehaviourTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
	UBlackboardComponent* BBComp;
};
