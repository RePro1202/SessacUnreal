// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IFF.h"
#include "AIController.h"
#include "../AIPawn.h"
#include "../AIStateComponent.h"

UBTDecorator_IFF::UBTDecorator_IFF()
{
	mCheckType = EIdentificationType::Unknown;
}

bool UBTDecorator_IFF::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();
	AAIPawn* AIPawn = Cast<AAIPawn>(Controller->GetPawn());

	if (!IsValid(AIPawn)) return false;

	EIdentificationType AIPawnIFF = AIPawn->GetIFF();

	if (AIPawnIFF == mCheckType) return true;
	else return false;
}
