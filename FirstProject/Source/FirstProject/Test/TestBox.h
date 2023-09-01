// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "TestBox.generated.h"

UCLASS()
class FIRSTPROJECT_API ATestBox : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = data, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> mBox;

	UPROPERTY(Category = data, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> mStaticMesh;

public:	
	// Sets default values for this actor's properties
	ATestBox();

private:
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

};
