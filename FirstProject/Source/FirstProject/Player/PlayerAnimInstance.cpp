// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "PlayerCharacter.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	mAnimType = EPlayerAnimType::Default;
	mOnGround = false;
	mMoveSpeed = 0.f;

	mFallRecoveryAdditive = 0.f;
	mAttackEnable = true;
	mAttackIndex = 0;

	mFallLandPosition = 0.14f;
	mCanJump = true;

	mTeleportAnimFlag = false;
}

void UPlayerAnimInstance::Attack()
{
	// 공격 가능 상태가 true이고 현재 공격 몽타주가 재생가능 상태여야 한다.
	if (!mAttackEnable || Montage_IsPlaying(mAttackMontage[mAttackIndex]))
		return;

	// 공격 불가능 상태로 만들어준다.
	mAttackEnable = false;

	// 공격 모션을 처음부터 재생시킬 수 있도록 한다.
	Montage_SetPosition(mAttackMontage[mAttackIndex], 0.f);

	// 몽타주를 재생시킨다.
	Montage_Play(mAttackMontage[mAttackIndex]);

	// 배열.Num() 배열의 수.
	mAttackIndex = (mAttackIndex + 1) % mAttackMontage.Num();
}

void UPlayerAnimInstance::Jump()
{
	if (Montage_IsPlaying(mFallRecovery))
	{
		mFallRecoveryAdditive = 0.f;
		Montage_Stop(0.1f, mFallRecovery);
	}

	mCanJump = false;
	mAnimType = EPlayerAnimType::Jump;
}

bool UPlayerAnimInstance::CanJump()
{
	return mCanJump;
}

void UPlayerAnimInstance::Teleport()
{
	Montage_SetPosition(mTeleportMontage, 0.f);
	Montage_Play(mTeleportMontage);
	
	if (mTeleportAnimFlag) false;
	mTeleportAnimFlag = true;
}

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	// 부모클래스의 NativeInitializeAnimation()를 먼저 호출해준다.
	// Super : 부모클래스를 의미한다.
	Super::NativeInitializeAnimation();

}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// Cast : 언리얼에서 제공하는 안전한 형변환 함수이다.
	// 언리얼 클래스들은 반드시 Cast 함수를 이용해서 형변환 해야한다.
	APlayerCharacter* Player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(Player))
	{
		UCharacterMovementComponent* Movement = Player->GetCharacterMovement();

		if (IsValid(Movement))
		{
			//mMoveSpeed값을 블렌드 스페이스 애니메이션에 이용해서 수치에 따라 재생.
			mMoveSpeed = Movement->Velocity.Length();
			mOnGround = Movement->IsMovingOnGround();
		}

		if (!mOnGround && mAnimType != EPlayerAnimType::Jump && mAnimType != EPlayerAnimType::Fall)
		{
			mAnimType = EPlayerAnimType::Fall;
		}

		// default 상태가 아닐 겨우 공격이 불가능 상태로 만들어준다.
		if (mAnimType != EPlayerAnimType::Default)
		{
			mAttackEnable = false;
		}

		// 땅을 밝고 있는 상태이고 애니메이션이 Fall일 경우 이제 막 땅을 밟게 되었다는 
		// 것 임으로 공격을 활성화한다.
		if (mOnGround && mAnimType == EPlayerAnimType::Fall)
		{
			mAttackEnable = true;
		}
	}

	/*
	// IsValid : 객체가 유효한지 검사한다.
	// nullptr일 경우 유효한 객체가 아니다.

	// Check는 C++의 assert 기능이다.
	// Check 괄호 안의 내용이 false일 경우 에러를 발생시킨다.
	//check(Player != nullptr);

	//checkf는 에러 발생시 메세지를 만들어 줄 수 있다.
	//checkf(Player != nullptr, TEXT("Player Cast Failed"));
	
	//check(Movement != nullptr);
	*/
}

void UPlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UPlayerAnimInstance::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();
}

void UPlayerAnimInstance::NativeUninitializeAnimation()
{
	Super::NativeUninitializeAnimation();
}

void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UPlayerAnimInstance::AnimNotify_TransitionFall()
{
	mAnimType = EPlayerAnimType::Fall;
}

void UPlayerAnimInstance::AnimNotify_LandEnd()
{
	mAnimType = EPlayerAnimType::Default;

	mFallRecoveryAdditive = 1.f;

	Montage_SetPosition(mFallRecovery, 0.f);
	Montage_Play(mFallRecovery);

	mCanJump = true;
}

void UPlayerAnimInstance::AnimNotify_RecorverEnd()
{
	mAnimType = EPlayerAnimType::Default;
	mFallRecoveryAdditive = 0.f;
}

void UPlayerAnimInstance::AnimNotify_Attack()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(Player))
	{
		Player->Attack1();
	}
}

void UPlayerAnimInstance::AnimNotify_Attack2()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(Player))
	{
		Player->Attack2();
	}
}

void UPlayerAnimInstance::AnimNotify_AttackEnable()
{
	mAttackEnable = true;
}

void UPlayerAnimInstance::AnimNotify_AttackEnd()
{
	mAttackEnable = true;
	mAttackIndex = 0;
}

void UPlayerAnimInstance::AnimNotify_BackRingEnd()
{
	mTeleportAnimFlag = false;
}

void UPlayerAnimInstance::AnimNotify_FootLeft()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(Player))
	{
		Player->FootInteraction(true);
	}
}

void UPlayerAnimInstance::AnimNotify_FootRight()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(Player))
	{
		Player->FootInteraction(false);
	}
}
