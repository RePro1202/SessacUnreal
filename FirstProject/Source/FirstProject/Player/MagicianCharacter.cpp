// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicianCharacter.h"

AMagicianCharacter::AMagicianCharacter()
{
	// FOjectFinder : �ּ��� �ε��ؼ� ����� �� ����.
	// � ������ �ҷ����� �� �� ���� ������ templat
	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGideon/Characters/Heroes/Gideon/Meshes/Gideon.Gideon'"));

	if (MeshAsset.Succeeded())
	{
		// ������ �ҷ��� SkeletalMesh�� 
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}
}
