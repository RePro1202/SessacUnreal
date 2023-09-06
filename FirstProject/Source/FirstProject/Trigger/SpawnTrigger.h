// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Trigger.h"
#include "SpawnTrigger.generated.h"


UCLASS()
class FIRSTPROJECT_API ASpawnTrigger : public ATrigger
{
	GENERATED_BODY()
	
public:
	ASpawnTrigger();

	UPROPERTY(Category = SpawnTarget, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<class AAISpawnPoint>> mList;

protected:
	void DoSomething() override;
};
