// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// CoreMinimal보다 많은 기능 포함
#include "EngineMinimal.h"
//#include "CoreMinimal.h"

#include "DrawDebughelpers.h"
#include "EngineGlobals.h"
#include "Engine.h"

#include "UObject/NoExportTypes.h"

// generated해더 위에다 include해야함.
#include "GameInfo.generated.h"

// log 출력 관련 작업
DECLARE_LOG_CATEGORY_EXTERN(FirstProject, Log, All);

#define   LOG_CALLINFO   (FString(__FUNCTION__) + TEXT("[") + FString::FromInt(__LINE__) + TEXT("]"))
// %s : 문자열을 받아와서 그 문자렬로 채워준다.
// %s는 FString을 바로 넣어줄 수 없다. 앞에 *을 붙여서 FString이 
// 가지고있는 문자열의 주소를 가지고 오고 그 주소를 넣어주어야 한다.
// 
// %d : 정수를 받아와서 그 정수를 문자열로 만들어서 채워준다.
// %f : 실수를 받아와서 그 실수를 문자열로 만들어서 채워준다.
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
