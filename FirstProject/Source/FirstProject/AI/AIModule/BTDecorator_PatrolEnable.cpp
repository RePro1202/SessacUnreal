// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_PatrolEnable.h"
#include "../AIPawn.h"
#include "../DefaultAIController.h"

UBTDecorator_PatrolEnable::UBTDecorator_PatrolEnable()
{
}

bool UBTDecorator_PatrolEnable::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AAIPawn* AIPawn = Cast<AAIPawn>(Controller->GetPawn());

	if (!IsValid(AIPawn))
		return false;

	AActor* CheckTarget = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject((TEXT("Target")));

	if (IsValid(CheckTarget))
		return false;

	

	return false;
}
