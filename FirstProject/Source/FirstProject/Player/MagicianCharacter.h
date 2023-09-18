// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerCharacter.h"
#include "MagicianCharacter.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPROJECT_API AMagicianCharacter : public APlayerCharacter
{
	GENERATED_BODY()

private:
	class ADecalEffect* mDecal;

public:
	AMagicianCharacter();
	


public:
	virtual void Attack1();
	virtual void Attack2();
};
