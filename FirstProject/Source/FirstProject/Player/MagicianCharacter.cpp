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
