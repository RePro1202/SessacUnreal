// Fill out your copyright notice in the Description page of Project Settings.

#include "../Effect/DecalEffect.h"
#include "MagicianCharacter.h"
#include "../Effect/DefaultEffact.h"
#include "../Projectile/ProjectileBase.h"

AMagicianCharacter::AMagicianCharacter()
{
	// FOjectFinder : �ּ��� �ε��ؼ� ����� �� ����.
	// � ������ �ҷ����� �� �� ���� ������ templat
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGideon/Characters/Heroes/Gideon/Meshes/Gideon.Gideon'"));

	if (MeshAsset.Succeeded())
	{
		// ������ �ҷ��� SkeletalMesh�� Character Ŭ������ ������ �ִ�
		// SkeletalMeshComponent�� �������ش�.
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	// Animation Blueprint Ŭ���� ���۷����� ���´�.
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
	// ���� ����. �÷��̾� �������� ���� �Ÿ���ŭ�� ���ݰŸ��� �ΰ�
	// ���� �浹üũ�� �����Ѵ�.

	FVector Start = GetActorLocation() + GetActorForwardVector() * 50.f;
	FVector End = Start + GetActorForwardVector() * 200.f;
	FCollisionQueryParams param(NAME_None, false, this);

	FHitResult result;

	bool Collision = GetWorld()->SweepSingleByChannel(result, Start, End, FQuat::Identity, 
		ECollisionChannel::ECC_GameTraceChannel4, FCollisionShape::MakeSphere(50.f), param);

	// ����� ��(������)���� ����Ѵ�.
#if ENABLE_DRAW_DEBUG

	// Collision ���� ���� true�� ��� red, false�� ��� green���� ����Ѵ�.
	FColor DrawColor = Collision ? FColor::Red : FColor::Green;

	// FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat() : Z���� ĳ������ �������� ������ִ�
	// ȸ�� ����� ���Ѵ�. (FMatrix�� ����� ���´�) �׷��� .ToQuat�� �̿��ؼ� FQuat(ȸ����)���� ��ȯ�Ѵ�.
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

			// ������ �����ֱ⸦ �����Ѵ�. 5.f�� �����ϸ� �����ǰ� 5�� �ڿ� ���ŵ�.
			Decal->SetLifeSpan(1.f);
		}
	}

}

void AMagicianCharacter::Attack2()
{
	FActorSpawnParameters ActorParam;
	ActorParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// ������ ��ġ�� ���´�. ������ ��ġ�� SkeletalMeshComponent�� �̿��ؼ� ���� �� �ִ�.
	FVector SocketLoc = GetMesh()->GetSocketLocation(TEXT("hand_l_Projectile"));

	AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(
		SocketLoc,
		GetActorRotation(), ActorParam);

	Projectile->SetCollisionProfile(TEXT("PlayerProjectile"));
}
