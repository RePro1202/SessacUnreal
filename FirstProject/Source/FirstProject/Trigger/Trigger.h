// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "Trigger.generated.h"

UENUM(BlueprintType)
enum class EUserTriggerType: uint8
{
	Player,
	Enemy,
	AllObject
};


UCLASS()
class FIRSTPROJECT_API ATrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrigger();

protected:
	UPROPERTY(Category = Componet, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> mBody;

	UPROPERTY(Category = Trigger, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EUserTriggerType mTriggerType;

public:
	void SetTriggerType(EUserTriggerType Type)
	{
		mTriggerType = Type;

		switch (mTriggerType)
		{
		case EUserTriggerType::Player:
			mBody->SetCollisionProfileName(TEXT("PlayerTrigger"));
			break;
		case EUserTriggerType::Enemy:
			mBody->SetCollisionProfileName(TEXT("EnemyTrigger"));
			break;
		case EUserTriggerType::AllObject:
			mBody->SetCollisionProfileName(TEXT("ObjectTrigger"));
			break;
		default:
			break;
		}
	}

protected:
	virtual void OnConstruction(const FTransform& Transform);


public:
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

};
