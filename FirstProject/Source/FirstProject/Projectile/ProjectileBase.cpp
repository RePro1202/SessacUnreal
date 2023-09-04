// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mBody = CreateDefaultSubobject<UBoxComponent>(TEXT("Body"));
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));

	SetRootComponent(mBody);

	mMesh->SetupAttachment(mBody);
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mBody->SetCollisionProfileName(TEXT("BlockAll"));

	mMovement->SetUpdatedComponent(mBody);

	mMovement->InitialSpeed = 1500.f;
	mMovement->OnProjectileStop.AddDynamic(this, &AProjectileBase::ProjectileStop);
	mMovement->ProjectileGravityScale = 0.1f;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/TestBlueprint/Sphere1.Sphere1'"));

	if (MeshAsset.Succeeded())
		mMesh->SetStaticMesh(MeshAsset.Object);


}

void AProjectileBase::ProjectileStop(const FHitResult& ImpactResult)
{
	Destroy();
}

void AProjectileBase::SetMeshAsset(const FString& Path)
{
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, *Path);

	if (IsValid(Mesh))
	{
		mMesh->SetStaticMesh(Mesh);
	}
}

void AProjectileBase::SetCollisionProfile(const FName& Name)
{
	mBody->SetCollisionProfileName(Name);
}

