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
	TArray<TObjectPtr<class AAISpawnPointWithVFX>> mList;

	UPROPERTY(Category = Data, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystem>	mParticleAsset;

	UPROPERTY(Category = Data, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase>	mSoundAsset;

protected:
	virtual void TriggerOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);
};
