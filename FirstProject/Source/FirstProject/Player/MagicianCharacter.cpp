// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicianCharacter.h"
#include "../Effect/DefaultEffact.h"

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

	if (Collision)
	{
		FActorSpawnParameters ActorParam;
		ActorParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


		ADefaultEffact* Effect = GetWorld()->SpawnActor<ADefaultEffact>(
			result.ImpactPoint, 
			FRotator::ZeroRotator, ActorParam);

		Effect->SetParticleAsset(TEXT("/Script/Engine.ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Ability/Defense/P_Shield_Spawn.P_Shield_Spawn'"));
		Effect->SetAudioAsset(TEXT("/Script/Engine.SoundWave'/Game/Sound/Fire1.Fire1'"));
	}

}

void AMagicianCharacter::Attack2()
{

}
