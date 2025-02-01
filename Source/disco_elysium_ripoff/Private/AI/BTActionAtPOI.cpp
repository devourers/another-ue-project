// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTActionAtPOI.h"

EBTNodeResult::Type UBTActionAtPOI::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory){

	OwnerComp.GetAIOwner();



	return EBTNodeResult::Succeeded;
}
