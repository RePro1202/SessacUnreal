// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicianCharacter.h"

AMagicianCharacter::AMagicianCharacter()
{
	// FOjectFinder : 애셋을 로딩해서 사용할 때 쓴다.
	// 어떤 에셋을 불러올지 알 수 없기 때문에 templat
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGideon/Characters/Heroes/Gideon/Meshes/Gideon.Gideon'"));

	if (MeshAsset.Succeeded())
	{
		// 위에서 불러온 SkeletalMesh를 Character 클래스가 가지고 있는
		// SkeletalMeshComponent에 지정해준다.
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	// Animation Blueprint 클래스 레퍼런스를 얻어온다.
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/Player/AB_Magician.AB_Magician_C'"));

	if (AnimClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimClass.Class);
	}


	GetCapsuleComponent()->SetCapsuleHalfHeight(92.f);
	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -92.0));
	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

}

void AMagicianCharacter::Attack1()
{
	// 근접 공격. 플레이어 전방으로 일정 거리만큼을 공격거리로 두고
	// 공격 충돌체크를 진행한다.
	// 
	// Sweep과 Overlap 2가지 종류로 나뉜다.
	// 여기서 Sweep과 Overlap은 Single과 Multi 2가지로 나뉜다.
	// Single은 가장 먼저 충돌한 하나의 객체에, Multi는 충돌된 모든 물체에 대해 충돌.
	// Trace 충돌채널을 이용해서 충돌을 진행한다.
	// 이 함수는 반환값으로 충돌이 있을 경우 true, 없을 경우 false를 반환한다.

	FVector Start = GetActorLocation() + GetActorForwardVector() * 50.f;
	FVector End = Start + GetActorForwardVector() * 200.f;
	FCollisionQueryParams param(NAME_None, false, this);

	FHitResult result;

	bool Collision = GetWorld()->SweepSingleByChannel(result, Start, End, FQuat::Identity, 
		ECollisionChannel::ECC_EngineTraceChannel4, FCollisionShape::MakeSphere(50.f), param);

	// 디버깅 용(에디터)으로 출력한다.
#if ENABLE_DRAW_DEBUG

	// Collision 값에 따라 true일 경우 red, false일 경우 green으로 출력한다.
	FColor DrawColor = Collision ? FColor::Red : FColor::Green;

	// FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat() : Z축을 캐릭터의 앞쪽으로 만들어주는
	// 회전 행렬을 구한다. (FMatrix로 결과가 나온다) 그래서 .ToQuat를 이용해서 FQuat(회전값)으로 변환한다.
	DrawDebugCapsule(GetWorld(), (Start + End) / 2, 100.f, 50.f,
		FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), DrawColor, false, 10.f);

#endif
}

void AMagicianCharacter::Attack2()
{

}
