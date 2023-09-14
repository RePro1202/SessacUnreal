// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolPoint.h"

APatrolPoint::APatrolPoint()
{
 	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(mRoot);
	mRoot->bVisualizeComponent = true;

}

void APatrolPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

void APatrolPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

