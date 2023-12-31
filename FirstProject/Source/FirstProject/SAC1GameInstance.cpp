// Fill out your copyright notice in the Description page of Project Settings.


#include "SAC1GameInstance.h"

USAC1GameInstance::USAC1GameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> PlayerData(TEXT("/Script/Engine.DataTable'/Game/Data/DT_PlayerData.DT_PlayerData'"));

	if (PlayerData.Succeeded())
	{
		mPlayerDataTable = PlayerData.Object;
	}
}

void USAC1GameInstance::Init()
{
	Super::Init();


}

const FPlayerDataTable* USAC1GameInstance::FindPlayerData(const FName& Name)
{
	return mPlayerDataTable->FindRow<FPlayerDataTable>(Name, TEXT(""));
}
