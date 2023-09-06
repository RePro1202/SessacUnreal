// Fill out your copyright notice in the Description page of Project Settings.


#include "AIGoblinPawn.h"
#include "AIStateComponent.h"
#include "DefaultAIAnimInstance.h"

AAIGoblinPawn::AAIGoblinPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	mBody->SetCapsuleHalfHeight(70.f);
	mBody->SetCapsuleRadius(32.f);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/Goblin/Mesh/Goblin_Base/SK_Goblin.SK_Goblin'"));
	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -70.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/AI/AM_AIGoblin.AM_AIGoblin_C'"));
	if (AnimAsset.Succeeded())
		mMesh->SetAnimInstanceClass(AnimAsset.Class);

	mMovement->MaxSpeed = 300;

	mState->InitState(EAIType::Goblin);
}

void AAIGoblinPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AAIGoblinPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AAIGoblinPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
