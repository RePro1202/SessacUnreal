// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

// uint8 : 1byte ��ȣ ���� �����̴�. 0~255 ���� ǥ�� �����ϴ�.
enum class EPlayerAnimType : uint8
{
	Default,
	Jump,
	Fall,
	Death
};

UCLASS()
class FIRSTPROJECT_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPlayerAnimInstance();

	virtual void NativeInitializeAnimation();

	virtual void NativeUpdateAnimation(float DeltaSeconds);
	
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds);
	
	virtual void NativePostEvaluateAnimation();
	
	virtual void NativeUninitializeAnimation();

	virtual void NativeBeginPlay();

};
