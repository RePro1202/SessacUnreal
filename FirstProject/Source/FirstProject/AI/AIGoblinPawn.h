// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIPawn.h"
#include "AIGoblinPawn.generated.h"


UCLASS()
class FIRSTPROJECT_API AAIGoblinPawn : public AAIPawn
{
	GENERATED_BODY()

public:
	AAIGoblinPawn();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 생성한 객체가 제거될때 호출된다.
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
