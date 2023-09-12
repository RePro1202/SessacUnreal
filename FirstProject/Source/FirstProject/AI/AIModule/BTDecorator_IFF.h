// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IFF.generated.h"


UCLASS()
class FIRSTPROJECT_API UBTDecorator_IFF : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_IFF();

protected:
	UPROPERTY(Category = Component, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EIdentificationType mCheckType;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;

};
