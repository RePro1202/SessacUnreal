// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultAIAnimInstance.h"
#include "AIPawn.h"

UDefaultAIAnimInstance::UDefaultAIAnimInstance()
{
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
			//mMoveSpeed���� ���� �����̽� �ִϸ��̼ǿ� �̿��ؼ� ��ġ�� ���� ���.
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
