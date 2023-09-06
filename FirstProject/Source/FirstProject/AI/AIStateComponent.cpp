// Fill out your copyright notice in the Description page of Project Settings.


#include "AIStateComponent.h"

// Sets default values for this component's properties
UAIStateComponent::UAIStateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	static ConstructorHelpers::FObjectFinder<UDataTable> AIData(TEXT("/Script/Engine.DataTable'/Game/Data/DT_PlayerData.DT_PlayerData'"));

	if (AIData.Succeeded())
	{
		mDataTabl = AIData.Object;
	}
}


// Called when the game starts
void UAIStateComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAIStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAIStateComponent::InitState(EAIType Type)
{
	FName TableName;

	switch (Type)
	{
	case EAIType::Serath:
		TableName = TEXT("Serath");
		break;
	case EAIType::Goblin:
		TableName = TEXT("Goblin");
		break;
	}

	//const FAIDataTable* Data = mDataTabl->FindRow<FAIDataTable>(TableName, TEXT(""));

	//mType = Data->Type;
	//mAttackPoint = Data->AttackPoint;
	//mArmorPoint = Data->ArmorPoint;
	//mHP = Data->HP;
	//mHPMax = Data->HP;
	//mMP = Data->MP;
	//mMPMax = Data->MP;
	//mLevel = Data->Level;
	//mExp = Data->Exp;
	//mGold = Data->Gold;
	//mMoveSpeed = Data->MoveSpeed;
	//mAttackDistance = Data->AttackDistance;
}
