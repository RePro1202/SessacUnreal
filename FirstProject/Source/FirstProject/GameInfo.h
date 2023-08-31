// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// CoreMinimal���� ���� ��� ����
#include "EngineMinimal.h"
//#include "CoreMinimal.h"

#include "DrawDebughelpers.h"
#include "EngineGlobals.h"
#include "Engine.h"

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

/**
 * 
 */
UCLASS()
class FIRSTPROJECT_API UGameInfo : public UObject
{
	GENERATED_BODY()
	
};
