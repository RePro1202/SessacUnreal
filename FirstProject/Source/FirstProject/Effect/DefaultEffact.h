// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "DefaultEffact.generated.h"

UCLASS()
class FIRSTPROJECT_API ADefaultEffact : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Category = data, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystemComponent> mParticle;

	UPROPERTY(Category = data, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAudioComponent> mAudio;

public:	
	// Sets default values for this actor's properties
	ADefaultEffact();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetParticleAsset(const FString& Path);
	void SetAudioAsset(const FString& Path);

};
