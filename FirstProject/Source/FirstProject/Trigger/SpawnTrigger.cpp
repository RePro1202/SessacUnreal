// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnTrigger.h"
#include "../AI/AISpawnPoint.h"

ASpawnTrigger::ASpawnTrigger()
{
	
}

void ASpawnTrigger::DoSomething()
{
	for (int i = 0; i < mList.Num(); i++)
	{
		mList[i]->StartSpawn();
	}

}
