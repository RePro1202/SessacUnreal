// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Engine/GameInstance.h"
#include "SAC1GameInstance.generated.h"


/*
	Player �� Pawn�� �޸𸮿��� �����ϸ� ������ �ִ� ��� �����Ͱ� ���Ű� �ȴ�. 
	������ PlayerState�� �޸𸮿� �״�� �����ִ´�.
	��, �����͸� ���� ���忡���� �����ؾ� �Ѵٸ� PlayerState�� Ȱ���Ͽ� �����͸� �����ؾ� �Ѵ�.

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
