// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "PlayerAnimInstance.h"
#include "SAC1PlayerState.h"
#include "../Material/SACPhysicalMaterial.h"

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

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));


	// 오버랩 이벤트 생성을 켜준다.
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	// 시뮬레이션 히트 이벤트 생성을 켜준다.
	GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);

	// OncomponetHit : Multicast + Dynamic 조합의 Delegate이다.
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &APlayerCharacter::BodyHit);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OverlapEnd);

	GetCapsuleComponent()->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	GetMesh()->bRenderCustomDepth = true;
	GetMesh()->SetCustomDepthStencilValue(0);
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
	// 점프 가능 상태인지 체크한다.
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

	ASAC1PlayerState* State = Cast<ASAC1PlayerState>(GetPlayerState());

	if (IsValid(State))
	{
		State->AddHP(-5);
	}
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

void APlayerCharacter::FootInteraction(bool Left)
{
	FVector FootLocation;

	if (Left)
		FootLocation = GetMesh()->GetSocketLocation(TEXT("Foot_L"));
	else
		FootLocation = GetMesh()->GetSocketLocation(TEXT("Foot_R"));

	FHitResult result;

	FCollisionQueryParams param(NAME_None, false, this);

	param.bReturnPhysicalMaterial = true;

	bool Collision = GetWorld()->SweepSingleByChannel(
		result,
		FootLocation, FootLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_Visibility,
		FCollisionShape::MakeSphere(50.f),
		param);

	if (Collision)
	{

	}
}
