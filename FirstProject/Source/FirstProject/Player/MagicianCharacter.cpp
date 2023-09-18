// Fill out your copyright notice in the Description page of Project Settings.

#include "../Effect/DecalEffect.h"
#include "MagicianCharacter.h"
#include "../Effect/DefaultEffact.h"
#include "../Projectile/ProjectileBase.h"

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
		ECollisionChannel::ECC_GameTraceChannel4, FCollisionShape::MakeSphere(50.f), param);

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

		Effect->SetParticleAsset(TEXT("/Script/Engine.ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_hit1.P_ky_hit1'"));
		Effect->SetAudioAsset(TEXT("/Script/Engine.SoundWave'/Game/Sound/Fire1.Fire1'"));


		FCollisionQueryParams param1(NAME_None, false, this);
		FHitResult LineResult;
		bool LineCollision = GetWorld()->LineTraceSingleByChannel(LineResult, result.ImpactPoint, result.ImpactPoint - FVector(0.0, 0.0, 200.0),
			ECollisionChannel::ECC_GameTraceChannel9, param1);

		if (LineCollision)
		{
			ADecalEffect* Decal = GetWorld()->SpawnActor<ADecalEffect>(
				result.ImpactPoint,
				FRotator::ZeroRotator, ActorParam);

			Decal->SetDecalMaterial(TEXT("/Script/Engine.Material'/Game/Megascans/Decals/Blood_Stain_sheuec0c/CustomBlood.CustomBlood'"));

			// 액터의 생명주기를 지정한다. 5.f를 지정하면 생성되고 5초 뒤에 제거됨.
			Decal->SetLifeSpan(1.f);
		}
	}

}

void AMagicianCharacter::Attack2()
{
	FActorSpawnParameters ActorParam;
	ActorParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// 소켓의 위치를 얻어온다. 소켓의 위치는 SkeletalMeshComponent를 이용해서 얻어올 수 있다.
	FVector SocketLoc = GetMesh()->GetSocketLocation(TEXT("hand_l_Projectile"));

	AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(
		SocketLoc,
		GetActorRotation(), ActorParam);

	Projectile->SetCollisionProfile(TEXT("PlayerProjectile"));
}
