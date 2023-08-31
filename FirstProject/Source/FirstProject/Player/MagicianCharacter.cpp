// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicianCharacter.h"

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
	// 
	// Sweep�� Overlap 2���� ������ ������.
	// ���⼭ Sweep�� Overlap�� Single�� Multi 2������ ������.
	// Single�� ���� ���� �浹�� �ϳ��� ��ü��, Multi�� �浹�� ��� ��ü�� ���� �浹.
	// Trace �浹ä���� �̿��ؼ� �浹�� �����Ѵ�.
	// �� �Լ��� ��ȯ������ �浹�� ���� ��� true, ���� ��� false�� ��ȯ�Ѵ�.

	FVector Start = GetActorLocation() + GetActorForwardVector() * 50.f;
	FVector End = Start + GetActorForwardVector() * 200.f;
	FCollisionQueryParams param(NAME_None, false, this);

	FHitResult result;

	bool Collision = GetWorld()->SweepSingleByChannel(result, Start, End, FQuat::Identity, 
		ECollisionChannel::ECC_EngineTraceChannel4, FCollisionShape::MakeSphere(50.f), param);
}

void AMagicianCharacter::Attack2()
{

}
