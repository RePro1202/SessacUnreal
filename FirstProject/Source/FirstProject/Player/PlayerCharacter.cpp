// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "PlayerAnimInstance.h"
#include "SAC1PlayerState.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	mSpringArm->SetRelativeLocation(FVector(0.0, 0.0, 160.0));
	mSpringArm->SetRelativeRotation(FRotator(-10.0, 90.0, 0.0));
	mSpringArm->TargetArmLength = 400.f;
	// �θ� ������Ʈ�� Mesh�� �����Ѵ�.
	mSpringArm->SetupAttachment(GetMesh());

	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mCamera->SetupAttachment(mSpringArm);

	mOriginSpringArmRotator = mSpringArm->GetRelativeRotation();
	mCameraRotationEnable = false;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));


	// ������ �̺�Ʈ ������ ���ش�.
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	// �ùķ��̼� ��Ʈ �̺�Ʈ ������ ���ش�.
	GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);

	// OncomponetHit : Multicast + Dynamic ������ Delegate�̴�.
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &APlayerCharacter::BodyHit);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OverlapEnd);

	GetCapsuleComponent()->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// SkeletalMesh�� GetAnimInstance �Լ��� �������ְ� �ִ�.
	// �� �Լ��� SkeletalMesh�� ������ AnimInstance Ŭ������ �̿��ؼ� ������ ��ü�� ������ �ִ�.
	// GetAnimInstance �Լ��� �ٷ� �� ��ü�� �������� �Լ��̴�.
	mPlayerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 1�� ���� : ����� �̸�
	// 2�� ���� : �Լ��� ȣ���� ��ü
	// 3�� ���� : �Լ��� �ּ�
	PlayerInputComponent->BindAxis(TEXT("MoveFront"), this, &APlayerCharacter::MoveFront);
	PlayerInputComponent->BindAxis(TEXT("MoveSide"), this, &APlayerCharacter::MoveSide);
	PlayerInputComponent->BindAxis(TEXT("RotationCharactor"), this, &APlayerCharacter::RotationCharacterYaw);
	PlayerInputComponent->BindAxis(TEXT("CameraPitch"), this, &APlayerCharacter::RotationCharacterPitch);
	PlayerInputComponent->BindAxis(TEXT("CameraZoom"), this, &APlayerCharacter::CameraZoom);

	PlayerInputComponent->BindAction(TEXT("RotationCamera"), EInputEvent::IE_Pressed, this, &APlayerCharacter::RotationCamera);
	PlayerInputComponent->BindAction(TEXT("RotationCamera"), EInputEvent::IE_Released, this, &APlayerCharacter::RotationCameraReleased);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &APlayerCharacter::JumpKey);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &APlayerCharacter::AttackKey);

}

void APlayerCharacter::TeleportBackward(float Scale)
{
	FVector moveVector = GetActorForwardVector() * Scale;
	TeleportTo(GetActorLocation() - moveVector, GetActorRotation(), false, true);

	mPlayerAnimInstance->Teleport();
}

void APlayerCharacter::MoveFront(float Scale)
{
	AddMovementInput(GetActorForwardVector(), Scale);
}

void APlayerCharacter::MoveSide(float Scale)
{
	AddMovementInput(GetActorRightVector(), Scale);
}

void APlayerCharacter::RotationCharacterYaw(float Scale)
{
	if (mCameraRotationEnable)
	{
		float Rot = GetWorld()->GetDeltaSeconds() * 180.f * Scale;

		mSpringArm->AddRelativeRotation(FRotator(0.0, (double)Rot, 0.0));
	}
	else 
	{
		AddControllerYawInput(Scale);
	}
}

void APlayerCharacter::RotationCharacterPitch(float Scale)
{
	if (mCameraRotationEnable)
	{
		FRotator CurrentSpringArmRotation = mSpringArm->GetRelativeRotation();

		float DeltaRotationPitch = GetWorld()->GetDeltaSeconds() * 180.f * Scale;
		float NewSpringArmPitch = CurrentSpringArmRotation.Pitch + DeltaRotationPitch;
		
		if (!IsRestrictedPitch(NewSpringArmPitch, CurrentSpringArmRotation))
		{
			mSpringArm->AddRelativeRotation(FRotator((double)DeltaRotationPitch, 0.0, 0.0));
		}
	}
}

bool APlayerCharacter::IsRestrictedPitch(float Pitch, FRotator CurrentSpringArmRotation)
{
	float minPitch = -50.f;
	float maxPitch = 10.f;

	if (Pitch < minPitch)
	{
		mSpringArm->SetRelativeRotation(FRotator(minPitch, CurrentSpringArmRotation.Yaw, CurrentSpringArmRotation.Roll));
		return true;
	}
	else if (Pitch > maxPitch)
	{
		mSpringArm->SetRelativeRotation(FRotator(maxPitch, CurrentSpringArmRotation.Yaw, CurrentSpringArmRotation.Roll));
		return true;
	}

	return false;
}

void APlayerCharacter::CameraZoom(float Scale)
{
	float Length = Scale * 10.f;

	mSpringArm->TargetArmLength -= Length;
}

void APlayerCharacter::RotationCamera()
{
	mCameraRotationEnable = true;
}

void APlayerCharacter::RotationCameraReleased()
{
	mSpringArm->SetRelativeRotation(mOriginSpringArmRotator);
	mCameraRotationEnable = false;
}

void APlayerCharacter::JumpKey()
{
	// ���� ���� �������� üũ�Ѵ�.
	if (CanJump() && mPlayerAnimInstance->CanJump())
	{
		Jump();
		mPlayerAnimInstance->Jump();
	}
}

void APlayerCharacter::AttackKey()
{
	mPlayerAnimInstance->Attack();
}

void APlayerCharacter::BodyHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, 
		FString::Printf(TEXT("Dest : %s"), *OtherActor->GetName()));

	// TODO : �浹ó��
}

void APlayerCharacter::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, 
		FString::Printf(TEXT("BeginOverlap Dest : %s"), *OtherActor->GetName()));

}

void APlayerCharacter::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, 
		FString::Printf(TEXT("EndOverlap Dest : %s"), *OtherActor->GetName()));

}

void APlayerCharacter::Attack1()
{
}

void APlayerCharacter::Attack2()
{
}
