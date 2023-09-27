// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "SelectPlayer.generated.h"

UCLASS()
class FIRSTPROJECT_API ASelectPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASelectPlayer();

private:
	TObjectPtr<AActor> mCursorPickActer;
	TObjectPtr<AActor> mSelectActer;

	UPROPERTY(EditAnywhere, mata = (AllowPrivateAccess = "true"))
	TObjectPtr<ACameraRig_Rail> mCameraRigRail;

	UPROPERTY(EditAnywhere, mata = (AllowPrivateAccess = "true"))
	TObjectPtr<ACameraActor> mKnightCamera;

	UPROPERTY(EditAnywhere, mata = (AllowPrivateAccess = "true"))
	float mCameraRigTime;

	float mCameraRigAddTime;
	float mCameraRIgPlayDir;

	bool mCameraTransition;

	EPlayerJob mSelectJob;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void Pick();

};
