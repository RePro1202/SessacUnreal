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
	}

	// IsValid : 객체가 유효한지 검사한다.
	// nullptr일 경우 유효한 객체가 아니다.

	// Check는 C++의 assert 기능이다.
	// Check 괄호 안의 내용이 false일 경우 에러를 발생시킨다.
	//check(Player != nullptr);

	//checkf는 에러 발생시 메세지를 만들어 줄 수 있다.
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
