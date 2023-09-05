// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIPawn.h"
#include "AISerathPawn.generated.h"

UCLASS()
class FIRSTPROJECT_API AAISerathPawn : public AAIPawn
{
	GENERATED_BODY()
	
public:
	AAISerathPawn();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// ������ ��ü�� ���ŵɶ� ȣ��ȴ�.
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
