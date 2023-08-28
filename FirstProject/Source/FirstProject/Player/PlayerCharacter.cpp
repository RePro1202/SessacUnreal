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
	// 부모 컴포넌트로 Mesh를 지정한다.
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

	// SkeletalMesh는 GetAnimInstance 함수를 지원해주고 있다.
	// 이 함수는 SkeletalMesh에 지정된 AnimInstance 클래스를 이용해서 생성한 객체를 가지고 있다.
	// GetAnimInstance 함수는 바로 이 객체를 꺼내오는 함수이다.
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

	// 1번 인자 : 축매핑 이름
	// 2번 인자 : 함수를 호출할 객체
	// 3번 인자 : 함수의 주소
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
	// 점프 가능 상태인지 체크한다.
	if (CanJump())
	{
		Jump();
		mPlayerAnimInstance->ChangeAnim(EPlayerAnimType::Jump);
	}
}

void APlayerCharacter::AttackKey()
{
}
