// Fill out your copyright notice in the Description page of Project Settings.


#include "Trigger.h"
#include "../Effect/DefaultEffact.h"

// Sets default values
ATrigger::ATrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mBody = CreateDefaultSubobject<UBoxComponent>(TEXT("Body"));
	SetRootComponent(mBody);
	mBody->bVisualizeComponent = true;
	mBody->SetBoxExtent(FVector(100.0, 100.0, 100.0));
	mBody->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	mBody->OnComponentBeginOverlap.AddDynamic(this, &ATrigger::OverlapBegin);

	mTriggerType = EUserTriggerType::AllObject;
}

void ATrigger::OnConstruction(const FTransform& Transform)
{
	// 변경사항이 있을때 호출됨.
	Super::OnConstruction(Transform);

	SetTriggerType(mTriggerType);
}

void ATrigger::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	LOG(TEXT("inObject"));

	FActorSpawnParameters ActorParam;
	ActorParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ADefaultEffact* Effect = GetWorld()->SpawnActor<ADefaultEffact>(OtherActor->GetActorLocation(), FRotator::ZeroRotator, ActorParam);

	Effect->SetParticleAsset(TEXT("/Script/Engine.ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Combat_Base/Resurrection/P_Resurrection_02.P_Resurrection_02'"));
	Effect->SetAudioAsset(TEXT("/Script/Engine.SoundWave'/Game/Sound/Fire3.Fire3'"));
}

