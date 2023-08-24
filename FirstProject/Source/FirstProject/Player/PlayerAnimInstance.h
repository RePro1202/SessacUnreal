// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

// uint8 : 1byte 부호 없는 정수이다. 0~255 까지 표현 가능하다.
UENUM(BlueprintType)
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

protected:
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float mMoveSpeed;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EPlayerAnimType mAnimType;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool mOnGround;

public:
	void ChangeAnim(EPlayerAnimType AnimType)
	{
		mAnimType = AnimType;
	}
	
public:
	virtual void NativeInitializeAnimation();

	virtual void NativeUpdateAnimation(float DeltaSeconds);
	
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds);
	
	virtual void NativePostEvaluateAnimation();
	
	virtual void NativeUninitializeAnimation();

	virtual void NativeBeginPlay();

public:
	// 노티파이 함수는 리턴타입은 void 이고 AnimNotify_노티파이이름() 
	// 의 형태로 함수를 제작해야 한다.

	UFUNCTION()
	void AnimNotify_TransitionFall();

	UFUNCTION()
	void AnimNotify_LandEnd();

	UFUNCTION()
	void RecorverEnd();
};
