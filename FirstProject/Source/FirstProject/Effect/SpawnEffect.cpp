// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnEffect.h"

ASpawnEffect::ASpawnEffect()
{
}

void ASpawnEffect::SetAudioAsset(const FString& Path)
{
	USoundBase* Sound = LoadObject<USoundBase>(nullptr, *Path);

	if (IsValid(Sound))
	{
		mAudio->SetSound(Sound);
	}
}

void ASpawnEffect::ParticleFinished()
{
	mAudio->Play();
}
