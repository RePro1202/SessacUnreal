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
	// ���� ���� ���°� true�̰� ���� ���� ��Ÿ�ְ� ������� ���¿��� �Ѵ�.
	if (!mAttackEnable || Montage_IsPlaying(mAttackMontage[mAttackIndex]))
		return;

	// ���� �Ұ��� ���·� ������ش�.
	mAttackEnable = false;

	// ���� ����� ó������ �����ų �� �ֵ��� �Ѵ�.
	Montage_SetPosition(mAttackMontage[mAttackIndex], 0.f);

	// ��Ÿ�ָ� �����Ų��.
	Montage_Play(mAttackMontage[mAttackIndex]);

	// �迭.Num() �迭�� ��.
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
	// �θ�Ŭ������ NativeInitializeAnimation()�� ���� ȣ�����ش�.
	// Super : �θ�Ŭ������ �ǹ��Ѵ�.
	Super::NativeInitializeAnimation();

}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// Cast : �𸮾󿡼� �����ϴ� ������ ����ȯ �Լ��̴�.
	// �𸮾� Ŭ�������� �ݵ�� Cast �Լ��� �̿��ؼ� ����ȯ �ؾ��Ѵ�.
	APlayerCharacter* Player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(Player))
	{
		UCharacterMovementComponent* Movement = Player->GetCharacterMovement();

		if (IsValid(Movement))
		{
			//mMoveSpeed���� ���� �����̽� �ִϸ��̼ǿ� �̿��ؼ� ��ġ�� ���� ���.
			mMoveSpeed = Movement->Velocity.Length();
			mOnGround = Movement->IsMovingOnGround();
		}

		if (!mOnGround && mAnimType != EPlayerAnimType::Jump && mAnimType != EPlayerAnimType::Fall)
		{
			mAnimType = EPlayerAnimType::Fall;
		}

		// default ���°� �ƴ� �ܿ� ������ �Ұ��� ���·� ������ش�.
		if (mAnimType != EPlayerAnimType::Default)
		{
			mAttackEnable = false;
		}

		// ���� ��� �ִ� �����̰� �ִϸ��̼��� Fall�� ��� ���� �� ���� ��� �Ǿ��ٴ� 
		// �� ������ ������ Ȱ��ȭ�Ѵ�.
		if (mOnGround && mAnimType == EPlayerAnimType::Fall)
		{
			mAttackEnable = true;
		}
	}

	/*
	// IsValid : ��ü�� ��ȿ���� �˻��Ѵ�.
	// nullptr�� ��� ��ȿ�� ��ü�� �ƴϴ�.

	// Check�� C++�� assert ����̴�.
	// Check ��ȣ ���� ������ false�� ��� ������ �߻���Ų��.
	//check(Player != nullptr);

	//checkf�� ���� �߻��� �޼����� ����� �� �� �ִ�.
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
