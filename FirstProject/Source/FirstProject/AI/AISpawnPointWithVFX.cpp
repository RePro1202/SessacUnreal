// Fill out your copyright notice in the Description page of Project Settings.


#include "AISpawnPointWithVFX.h"
#include "AIPawn.h"

AAISpawnPointWithVFX::AAISpawnPointWithVFX()
{
	mParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	mParticle->SetupAttachment(mRoot);
}

void AAISpawnPointWithVFX::SetVFX(TObjectPtr<UParticleSystem> ParticleAsset, TObjectPtr<USoundBase> SoundAsset)
{
	if (!IsValid(mSpawnClass))
		return;

	mSoundAsset = SoundAsset;

	if (IsValid(ParticleAsset))
	{
		mParticle->SetTemplate(ParticleAsset);
		mParticle->ActivateSystem(true);
	}

	//
}

void AAISpawnPointWithVFX::BeginPlay()
{
	Super::BeginPlay();

	mParticle->OnSystemFinished.AddDynamic(this, &AAISpawnPointWithVFX::ParticleFinish);
}

void AAISpawnPointWithVFX::ParticleFinish(UParticleSystemComponent* System)
{
	// ���� ���.
	UGameplayStatics::PlaySoundAtLocation(this, mSoundAsset,
		GetActorLocation());

	FActorSpawnParameters	ActorParam;
	ActorParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// Template ������ Ư�� ���͸� �־��ָ� �ش� ���͸� ������ ���͸�
	// �������ش�.
	//ActorParam.Template = mSpawnClass->GetDefaultObject();

	// UClass�� ������ �ִ� �� Ÿ���� �⺻ ������Ʈ�� ���´�.
	TObjectPtr<AAIPawn> DefaultObj = Cast<AAIPawn>(mSpawnClass->GetDefaultObject());

	float	HalfHeight = 0.f;

	// �⺻ ������Ʈ�� ��ȿ�� ��� ĸ���� ���� ���̸� ���´�.
	if (IsValid(DefaultObj))
		HalfHeight = DefaultObj->GetHalfHeight();

	LOG(TEXT("HalfHeight : %.5f"), HalfHeight);

	//GetWorld()->SpawnActor<AAIPawn>(mSpawnClass,
	//	GetActorLocation() + FVector(0.0, 0.0, (double)HalfHeight),
	//	GetActorRotation(), ActorParam);
	StartSpawn();
}

