// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/ActorComponent.h"
#include "AIStateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRSTPROJECT_API UAIStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAIStateComponent();

protected:
	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EAIType mType;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 mAttackPoint;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 mArmorPoint;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 mHP;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 mHPMax;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 mMP;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 mMPMax;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 mLevel;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 mExp;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 mGold;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float mMoveSpeed;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float mAttackDistance;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float mInteractionDistance;

	UDataTable* mDataTabl;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void InitState(EAIType Type);

	float GetAttackDistance() {
		return mAttackDistance;
	}

	float GetInteractionDistance() {
		return mInteractionDistance;
	}
};
