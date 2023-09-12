// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Pawn.h"
#include "AIPawn.generated.h"

UCLASS()
class FIRSTPROJECT_API AAIPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIPawn();

protected:
	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> mBody;

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> mMesh;

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement> mMovement;

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAIStateComponent> mState;

	TObjectPtr<class UDefaultAIAnimInstance> mAnim;


	// ������ ��������Ʈ�� �˰� �ְ� ���ش�.
	// ���� ����Ʈ�� �̿��ؼ� ������ ��ü�� �ƴ� ��� None�� �� �ִ�.
	TObjectPtr<class AAISpawnPoint> mSpawnPoint;

	bool mAttackEnd;

	UPROPERTY(Category = Component, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EIdentificationType mIFFType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// ������ ��ü�� ���ŵɶ� ȣ��ȴ�.
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	const TObjectPtr<class UAIStateComponent>& GetAIState()	const
	{
		return mState;
	}

	const TObjectPtr<class UDefaultAIAnimInstance>& GetAIAnimInstance()	const
	{
		return mAnim;
	}


	float GetHalfHeight() const
	{
		return mBody->GetScaledCapsuleHalfHeight();
	}

	float GetCapsuleRadius() const
	{
		return mBody->GetScaledCapsuleRadius();
	}

	bool GetAttackEnd() const
	{
		return mAttackEnd;
	}

	EIdentificationType GetIFF() const
	{
		return mIFFType;
	}

	void SetAttackEnd(bool AttackEnd)
	{
		mAttackEnd = AttackEnd;
	}

	void SetSpawnPoint(class AAISpawnPoint* SpawnPoint);


public:
	void SetCollisionProfile(const FName& Name);

};
