// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultAIAnimInstance.h"
#include "AIPawn.h"

UDefaultAIAnimInstance::UDefaultAIAnimInstance()
{
	mAnimType = EAIAnimType::Idle;
	mMoveSpeed = 0.f;
}

void UDefaultAIAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UDefaultAIAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AAIPawn* Pawn = Cast<AAIPawn>(TryGetPawnOwner());

	if (IsValid(Pawn))
	{
		UMovementComponent* Movement = Pawn->GetMovementComponent();

		if (IsValid(Movement))
		{
			//mMoveSpeed값을 블렌드 스페이스 애니메이션에 이용해서 수치에 따라 재생.
			mMoveSpeed = Movement->Velocity.Length();
		}
		else 
		{
			LOG(TEXT("null movement"))
		}
	}
	else
	{
		LOG(TEXT("null pawn"))
	}
}

void UDefaultAIAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UDefaultAIAnimInstance::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();
}

void UDefaultAIAnimInstance::NativeUninitializeAnimation()
{
	Super::NativeUninitializeAnimation();
}

void UDefaultAIAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UDefaultAIAnimInstance::AnimNotify_Attack()
{

}

void UDefaultAIAnimInstance::AnimNotify_AttackEnd()
{
	AAIPawn* AIPawn = Cast<AAIPawn>(TryGetPawnOwner());

	if (IsValid(AIPawn))
	{
		AIPawn->SetAttackEnd(true);
	}
}
