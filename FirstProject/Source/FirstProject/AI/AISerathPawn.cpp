// Fill out your copyright notice in the Description page of Project Settings.


#include "AISerathPawn.h"

AAISerathPawn::AAISerathPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	mBody->SetCapsuleHalfHeight(92.f);
	mBody->SetCapsuleRadius(32.f);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonSerath/Characters/Heroes/Serath/Meshes/Serath.Serath'"));
	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -92.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));
}

void AAISerathPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AAISerathPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AAISerathPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
