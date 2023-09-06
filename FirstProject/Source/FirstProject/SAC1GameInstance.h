// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Engine/GameInstance.h"
#include "SAC1GameInstance.generated.h"


/*
	Player 용 Pawn은 메모리에서 제거하면 가지고 있던 모든 데이터가 제거가 된다. 
	하지만 PlayerState는 메모리에 그대로 남아있는다.
	즉, 데이터를 다음 월드에서도 유지해야 한다면 PlayerState를 활용하여 데이터를 저장해야 한다.

*/

UCLASS()
class FIRSTPROJECT_API USAC1GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	USAC1GameInstance();

private:
	TObjectPtr<UDataTable> mPlayerDataTable;

public:
	virtual void Init();

public:
	const FPlayerDataTable* FindPlayerData(const FName& Name);
	
};
