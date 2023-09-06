// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "AISpawnPoint.h"
#include "AISpawnPointWithVFX.generated.h"


UCLASS()
class FIRSTPROJECT_API AAISpawnPointWithVFX : public AAISpawnPoint
{
	GENERATED_BODY()

public:
	AAISpawnPointWithVFX();
	
private:
	UPROPERTY(Category = data, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystemComponent> mParticle;

	UPROPERTY(Category = data, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystem> mParticleAsset;
	
	TObjectPtr<USoundBase>	mSoundAsset;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void ParticleFinish(UParticleSystemComponent* System);

	void SetVFX(TObjectPtr<UParticleSystem> ParticleAsset, TObjectPtr<USoundBase> SoundAsset);

};
