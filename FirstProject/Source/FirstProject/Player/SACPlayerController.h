// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "SACPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPROJECT_API ASACPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASACPlayerController();

private:
	TObjectPtr<AActor> mCursorPickActor;

protected:
	virtual void OnConstruction(const FTransform& Transform);
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	void ChangePickOutLine(int32 StencilValue);
};
