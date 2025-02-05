// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CompanionAIController.h"
#include "../PointAndClickPlayerController.h"
#include "AI/Companion.h"

ACompanionAIController::ACompanionAIController() {
	BehaviourTree = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behaviour Tree"));
	BBComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
}

void ACompanionAIController::OnPossess(APawn* pawn){
	Super::OnPossess(pawn);

	Companion = Cast<ACompanion>(pawn);
	if (Companion)
		BBComp->InitializeBlackboard(*BBComp->GetBlackboardAsset());

	BehaviourTree->StartLogic();
}

void ACompanionAIController::BeginPlay(){
	Super::BeginPlay();
	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	APointAndClickPlayerController* casted_controller = Cast<APointAndClickPlayerController>(controller);
	if (casted_controller) {
		casted_controller->PlayerTargetLocationChanged.AddUniqueDynamic(this, &ACompanionAIController::OnPlayerTargetLocationUpdated);
	}
}


void ACompanionAIController::OnPlayerTargetLocationUpdated(const FVector& target_location) {
	//select some point in radius around?
	BBComp->SetValueAsVector("PlayerTargetLocation", target_location);
}
