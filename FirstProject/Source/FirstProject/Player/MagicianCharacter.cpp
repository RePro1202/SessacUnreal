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

	GetCapsuleComponent()->SetCapsuleHalfHeight(92.f);
	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -92.0));
	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

}
