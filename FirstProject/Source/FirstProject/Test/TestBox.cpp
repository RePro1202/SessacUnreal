// Fill out your copyright notice in the Description page of Project Settings.


#include "TestBox.h"
#include "../Effect/DefaultEffact.h"

// Sets default values
ATestBox::ATestBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mBox = CreateDefaultSubobject<UBoxComponent>("Box");
	SetRootComponent(mBox);
	mBox->SetBoxExtent(FVector(130.0, 60.0, 110.0));
	mBox->SetGenerateOverlapEvents(true);
	mBox->SetCollisionProfileName(TEXT("TestOverlap"));
	mBox->OnComponentBeginOverlap.AddDynamic(this, &ATestBox::OverlapBegin);


	mStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("staticMesh");
	mStaticMesh->SetupAttachment(mBox);
	mStaticMesh->SetRelativeLocation(FVector(0.0, 0.0, -120.0));
	mStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mStaticMesh->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/TMHighTechPack1/HighTech/meshes/TV03/SM_TV03.SM_TV03'"));
	if (MeshAsset.Succeeded())
	{
		mStaticMesh->SetStaticMesh(MeshAsset.Object);
	}
}

void ATestBox::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FActorSpawnParameters ActorParam;
	ActorParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ADefaultEffact* Effect = GetWorld()->SpawnActor<ADefaultEffact>(GetActorLocation(), FRotator::ZeroRotator, ActorParam);

	Effect->SetParticleAsset(TEXT("/Script/Engine.ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Combat_Base/Resurrection/P_Resurrection_02.P_Resurrection_02'"));
	Effect->SetAudioAsset(TEXT("/Script/Engine.SoundWave'/Game/Sound/Fire3.Fire3'"));
}

