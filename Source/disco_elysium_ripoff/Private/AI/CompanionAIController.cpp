// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CompanionAIController.h"
#include "../PointAndClickPlayerController.h"
#include "../ProtagClass.h"
#include "AI/Companion.h"

ACompanionAIController::ACompanionAIController() {
	BehaviourTree = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behaviour Tree"));
	BBComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
}

void ACompanionAIController::OnPossess(APawn* pawn){
	Super::OnPossess(pawn);

	companion_ = Cast<ACompanion>(pawn);
	if (companion_)
		BBComp->InitializeBlackboard(*BBComp->GetBlackboardAsset());

	BehaviourTree->StartLogic();
}

void ACompanionAIController::BeginPlay(){
	Super::BeginPlay();
	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	APointAndClickPlayerController* casted_controller = Cast<APointAndClickPlayerController>(controller);
	if (casted_controller) 
		casted_controller->PlayerTargetLocationChanged.AddUniqueDynamic(this, &ACompanionAIController::OnPlayerTargetLocationUpdated);
	
	protag_ = Cast<AProtagClass>(controller->GetPawn());
	if (protag_) {
		protag_->PlayerTeleported.AddUniqueDynamic(this, &ACompanionAIController::OnPlayerTeleported);
		GetPathFollowingComponent()->SetAcceptanceRadius(150.0f);
	}
}


void ACompanionAIController::OnPlayerTargetLocationUpdated(const FVector& target_location) {
	if (!companion_->IsSelectedAsDestination()) {
		FVector int_char = (companion_->GetInteractionHitbox()->GetComponentLocation() - companion_->GetActorLocation());
		BBComp->SetValueAsVector("PlayerTargetLocation", target_location - int_char);
	}
	else {
		BBComp->ClearValue("PlayerTargetLocation");
	}
		
}

void ACompanionAIController::OnPlayerTeleported(const FVector& teleport_location) {
	if (companion_)
		companion_->TeleportTo(teleport_location, protag_->GetActorRotation());
}