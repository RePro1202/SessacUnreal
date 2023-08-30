// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionTester.h"

// Sets default values
ACollisionTester::ACollisionTester()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mCapsule = CreateDefaultSubobject<UCapsuleComponent>("collision");
	mCapsule->SetNotifyRigidBodyCollision(true);
	mCapsule->OnComponentHit.AddDynamic(this, &ACollisionTester::Hit);
	mCapsule->SetCollisionProfileName(TEXT("Test"));
	SetRootComponent(mCapsule);

	mStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("staticMesh");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/TMHighTechPack1/HighTech/meshes/Computer03/SM_Computer03.SM_Computer03'"));
	mStaticMesh->SetupAttachment(mCapsule);
	mStaticMesh->SetStaticMesh(MeshAsset.Object);
	mStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ACollisionTester::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACollisionTester::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACollisionTester::Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue,
		FString::Printf(TEXT("Dest : %s"), *OtherActor->GetName()));

}

