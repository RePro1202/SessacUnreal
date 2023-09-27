// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectPlayer.h"

// Sets default values
ASelectPlayer::ASelectPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mCameraRigTime = 5.f;
	mCameraRigAddTime = 0.f;
	mCameraTransition = false;
	mCameraRIgPlayDir = 1.f;

	mSelectJob = EPlayerJob::None;
}

// Called when the game starts or when spawned
void ASelectPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASelectPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult result;

	bool Collision = GetWorld()->GetFirstPlayerController()
		->GetHitResultUnderCursor(ECC_GameTraceChannel10, false, result);

	if (Collision)
	{
		USkeletalMeshComponent* MeshCom = nullptr;

		if (IsValid(mCursorPickActer) && mCursorPickActer != result.GetActor())
		{
			MeshCom = mCursorPickActer->GetComponentByClass<USkeletalMeshComponent>();

			if (IsValid(MeshCom))
			{
				MeshCom->SetRenderCustomDepth(false);
			}
		}

		mCursorPickActer = result.GetActor();

		MeshCom = mCursorPickActer->GetComponentByClass<USkeletalMeshComponent>();

		if (IsValid(MeshCom))
		{
			MeshCom->SetRenderCustomDepth(true);
		}
	}
	else if (IsValid(mCursorPickActer))
	{
		USkeletalMeshComponent* MeshCom = mCursorPickActer->GetComponentByClass<USkeletalMeshComponent>();

		if (IsValid(MeshCom))
		{
			MeshCom->SetRenderCustomDepth(false);
		}

		mCursorPickActer = nullptr;
	}

	if (mCameraTransition)
	{
		mCameraRigAddTime += DeltaTime * mCameraRIgPlayDir;

		if (mCameraRigAddTime >= mCameraRigTime)
		{
			mCameraRigAddTime = mCameraRigTime;
			mCameraTransition = false;
		}
		else if (mCameraRigAddTime <= 0.f)
		{
			mCameraRigAddTime = 0.f;
			mCameraTransition = false;
		}

		float RigRatio = mCameraRigAddTime / mCameraRigTime;

		mCameraRigRail->CurrentPositionOnRail = RigRatio;
	}

}

// Called to bind functionality to input
void ASelectPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Select"), EInputEvent::IE_Pressed, this, &ASelectPlayer::Pick);

}

void ASelectPlayer::Pick()
{
	if (IsValid(mCursorPickActer))
	{
		mSelectActer = mCursorPickActer;
	}

}

