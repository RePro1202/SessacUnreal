// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "AISpawnPoint.generated.h"

UCLASS()
class FIRSTPROJECT_API AAISpawnPoint : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAISpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> mRoot;

#if WITH_EDITORONLY_DATA
	UPROPERTY()
	TObjectPtr<UArrowComponent> mArrow;
#endif
	UPROPERTY(Category = Component, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf <class AAIPawn> mSpawnClass;

	TObjectPtr<class AAIPawn> mSpawnObject;

	UPROPERTY(Category = Component, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float mSpawnTime;

	float mTime;

	UPROPERTY(Category = data, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool PlaySpawnEffect;

	UPROPERTY(Category = data, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystem> mParticle;

	UPROPERTY(Category = data, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> mAudio;


public:
	void ClearObject();
	void StartSpawn();

private:
	void SpawnObject();



};
