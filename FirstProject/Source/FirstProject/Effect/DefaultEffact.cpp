// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultEffact.h"

// Sets default values
ADefaultEffact::ADefaultEffact()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	mAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));

	SetRootComponent(mParticle);
	mAudio->SetupAttachment(mParticle);

}

// Called when the game starts or when spawned
void ADefaultEffact::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefaultEffact::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADefaultEffact::SetParticleAsset(const FString& Path)
{
	// FString은 역참조를 하면 이 문자열 클래스가 가지고 있는 문자열 포인터(TCHAR*)를 반환.
	// 그래서 2번째 인자에 Path의 역참조를 통해 에셋의 경로를 넣어주면 해당 에셋을 불러온다.
	UParticleSystem* Particle = LoadObject<UParticleSystem>(nullptr, *Path);

	if (IsValid(Particle))
	{
		mParticle->SetTemplate(Particle);
	}
}

void ADefaultEffact::SetAudioAsset(const FString& Path)
{
	USoundBase* Sound = LoadObject<USoundBase>(nullptr, *Path);

	if (IsValid(Sound))
	{
		mAudio->SetSound(Sound);
	}
}

