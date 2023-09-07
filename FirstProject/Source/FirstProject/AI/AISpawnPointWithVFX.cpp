// Fill out your copyright notice in the Description page of Project Settings.


#include "AISpawnPointWithVFX.h"
#include "AIPawn.h"

AAISpawnPointWithVFX::AAISpawnPointWithVFX()
{
	mParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	mParticle->SetupAttachment(mRoot);
}

void AAISpawnPointWithVFX::SetVFX(TObjectPtr<UParticleSystem> ParticleAsset, TObjectPtr<USoundBase> SoundAsset)
{
	if (!IsValid(mSpawnClass))
		return;

	mSoundAsset = SoundAsset;

	if (IsValid(ParticleAsset))
	{
		mParticle->SetTemplate(ParticleAsset);
		mParticle->ActivateSystem(true);
	}
}

void AAISpawnPointWithVFX::BeginPlay()
{
	Super::BeginPlay();

	mParticle->OnSystemFinished.AddDynamic(this, &AAISpawnPointWithVFX::ParticleFinish);
	
}

void AAISpawnPointWithVFX::ParticleFinish(UParticleSystemComponent* System)
{
	// 사운드 재생.
	UGameplayStatics::PlaySoundAtLocation(this, mSoundAsset, GetActorLocation());

	StartSpawn();

	LOG(TEXT("Particle Over"));
}

