// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "DefaultEffact.h"
#include "SpawnEffect.generated.h"


UCLASS()
class FIRSTPROJECT_API ASpawnEffect : public ADefaultEffact
{
	GENERATED_BODY()

public:
	ASpawnEffect();

public:
	virtual void SetAudioAsset(const FString& Path) override;
	
protected:
	virtual void ParticleFinished() override;
	
};
