// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "PlayerAnimInstance.h"

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
		float Rot = GetWorld()->GetDeltaSeconds() * 180.f * Scale;

		FRotator CurrentSpringArmRotation = mSpringArm->GetRelativeRotation();
		float NewSpringArmPitch = Rot + CurrentSpringArmRotation.Pitch;

		if (NewSpringArmPitch >= -50.f && NewSpringArmPitch <= 10)
		{
			mSpringArm->AddRelativeRotation(FRotator((double)Rot, 0.0, 0.0));
		}
		else if (NewSpringArmPitch < -50.f)
		{
			mSpringArm->SetRelativeRotation(FRotator(-50.f, CurrentSpringArmRotation.Yaw, CurrentSpringArmRotation.Roll));
		}
		else if (NewSpringArmPitch > 10)
		{
			mSpringArm->SetRelativeRotation(FRotator(10.f, CurrentSpringArmRotation.Yaw, CurrentSpringArmRotation.Roll));
		}
	}
}

void APlayerCharacter::RestrictPitch(float Pitch)
{
	if(Pitch < -50.f)

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
	if (CanJump())
	{
		Jump();
		mPlayerAnimInstance->ChangeAnim(EPlayerAnimType::Jump);
	}
}

void APlayerCharacter::AttackKey()
{
}
