// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "SACPhysicalMaterial.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPROJECT_API USACPhysicalMaterial : public UPhysicalMaterial
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> mSound;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystem> mParticle;

public:
	USoundBase* GetSound() const
	{
		return mSound;
	}
	
	UParticleSystem* GetParticle() const
	{
		return mParticle;
	}

};
