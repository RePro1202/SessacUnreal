// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "CharacterSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPROJECT_API UCharacterSelectWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UButton* mStartButton;

public:
	void EnableStartButton(bool Enable);

public:
	virtual void NativeConstruct();

private:
	UFUNCTION()
	void StartButtonClick();
	
};
