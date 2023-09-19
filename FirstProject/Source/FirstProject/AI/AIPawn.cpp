// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPawn.h"
#include "AISpawnPoint.h"
#include "AIStateComponent.h"
#include "DefaultAIController.h"
#include "DefaultAIAnimInstance.h"

// Sets default values
AAIPawn::AAIPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mIFFType = EIdentificationType::Unknown;
	mAttackEnd = false;
	// Controller의 Yaw 회전에 매칭한다.
	//bUseControllerRotationYaw = true;

	mBody = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Body"));
	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	mState = CreateDefaultSubobject<UAIStateComponent>(TEXT("State"));

	SetRootComponent(mBody);
	mMesh->SetupAttachment(mBody);
	mMovement->SetUpdatedComponent(mBody);

	mBody->SetCollisionProfileName(TEXT("AI"));
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ADefaultAIController::StaticClass();


	mHit = false;
	mHitTimer = 0.f;

	mMesh->bRenderCustomDepth = true;
	// 0 ~ 255 사이의 원하는 값.
	mMesh->SetCustomDepthStencilValue(0);
}

void AAIPawn::SetSpawnPoint(AAISpawnPoint* SpawnPoint)
{
	mSpawnPoint = SpawnPoint;
}

float AAIPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	LOG(TEXT("Damage : %.5f"), Damage);

	mHit = true;
	mHitTimer = 0.f;

	if (!mHitTimerHandel.IsValid())
	{

		GetWorld()->GetTimerManager().SetTimer(mHitTimerHandel, this, &AAIPawn::HitTimer, 0.2f);
	}

	for (auto& Material : mMaterialArray)
	{
		Material->SetVectorParameterValue(TEXT("HitColor"), FVector(1.0, 0.0, 0.0));
	}

	return Damage;
}

void AAIPawn::HitTimer()
{
	mHit = true;

	for (auto& Material : mMaterialArray)
	{
		Material->SetVectorParameterValue(TEXT("HitColor"), FVector(1.0, 1.0, 1.0));
	}

	GetWorld()->GetTimerManager().ClearTimer(mHitTimerHandel);
}

void AAIPawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// Material Element Count
	int32 ElementCount = mMesh->GetNumMaterials();

	for (int32 i = 0; i < ElementCount; i++)
	{
		UMaterialInstanceDynamic* Mtl = mMesh->CreateDynamicMaterialInstance(i);

		mMaterialArray.Add(Mtl);
	}
	
}

// Called when the game starts or when spawned
void AAIPawn::BeginPlay()
{
	Super::BeginPlay();
	
	mAnim = Cast<UDefaultAIAnimInstance>(mMesh->GetAnimInstance());
}

void AAIPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (IsValid(mSpawnPoint))
		mSpawnPoint->ClearObject();
}

// Called every frame
void AAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//AddMovementInput(GetActorForwardVector());

	//if (mHitTimer >= 1.f)
	//{
	//	for (auto& Material : mMaterialArray)
	//	{
	//		Material->SetVectorParameterValue(TEXT("HitColor"), FVector(1.0, 1.0, 1.0));
	//	}
	//
	//	mHit = false;
	//}
	//if (mHit)
	//{
	//	mHitTimer += DeltaTime;
	//}
}

void AAIPawn::SetCollisionProfile(const FName& Name)
{
	mBody->SetCollisionProfileName(Name);
}

