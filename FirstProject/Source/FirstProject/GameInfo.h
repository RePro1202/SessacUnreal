// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// CoreMinimal���� ���� ��� ����
#include "EngineMinimal.h"
//#include "CoreMinimal.h"

#include "DrawDebughelpers.h"
#include "EngineGlobals.h"
#include "Engine.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "UObject/NoExportTypes.h"

// generated�ش� ������ include�ؾ���.
#include "GameInfo.generated.h"

// log ��� ���� �۾�
DECLARE_LOG_CATEGORY_EXTERN(FirstProject, Log, All);

#define   LOG_CALLINFO   (FString(__FUNCTION__) + TEXT("[") + FString::FromInt(__LINE__) + TEXT("]"))
// %s : ���ڿ��� �޾ƿͼ� �� ���ڷķ� ä���ش�.
// %s�� FString�� �ٷ� �־��� �� ����. �տ� *�� �ٿ��� FString�� 
// �������ִ� ���ڿ��� �ּҸ� ������ ���� �� �ּҸ� �־��־�� �Ѵ�.
// 
// %d : ������ �޾ƿͼ� �� ������ ���ڿ��� ���� ä���ش�.
// %f : �Ǽ��� �޾ƿͼ� �� �Ǽ��� ���ڿ��� ���� ä���ش�.
#define   LOG(Format, ...)   UE_LOG(FirstProject, Warning, TEXT("%s : %s"), *LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
#define   LOGSTRING(str)      UE_LOG(FirstProject, Warning, TEXT("%S : %S"), *LOG_CALLINFO, *str)

UENUM(BlueprintType)
enum class EPlayerJob : uint8
{
	None,
	Knight,
	Archer,
	Magicion
};

//  FTableRowBase ����ü�� ��ӹ޾ƾ� ���������̺� �� ����ü�� ���� �� �ִ�.
USTRUCT(BlueprintType)
struct FPlayerDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPlayerJob Job;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 AttackPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 ArmorPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 MP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Gold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float AttackDistance;


};


UENUM(BlueprintType)
enum class EAIType : uint8
{
	None,
	Serath,
	Goblin
};

USTRUCT(BlueprintType)
struct FAIDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EAIType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 AttackPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 ArmorPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 MP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Gold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float AttackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float InteractionDistance;
};

UENUM(BlueprintType)
enum class EIdentificationType : uint8
{
	Unknown,
	Frend,
	Foe
};


UCLASS()
class FIRSTPROJECT_API UGameInfo : public UObject
{
	GENERATED_BODY()
	
};
