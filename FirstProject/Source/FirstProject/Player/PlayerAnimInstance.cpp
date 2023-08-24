// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "PlayerCharacter.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	mAnimType = EPlayerAnimType::Default;
	mOnGround = false;
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
	}

	// IsValid : ��ü�� ��ȿ���� �˻��Ѵ�.
	// nullptr�� ��� ��ȿ�� ��ü�� �ƴϴ�.

	// Check�� C++�� assert ����̴�.
	// Check ��ȣ ���� ������ false�� ��� ������ �߻���Ų��.
	//check(Player != nullptr);

	//checkf�� ���� �߻��� �޼����� ����� �� �� �ִ�.
	//checkf(Player != nullptr, TEXT("Player Cast Failed"));
	
	//check(Movement != nullptr);
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
