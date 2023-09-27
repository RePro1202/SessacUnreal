// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectWidget.h"

void UCharacterSelectWidget::EnableStartButton(bool Enable)
{
	mStartButton->SetIsEnabled(Enable);
}

void UCharacterSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mStartButton = Cast<UButton>(GetWidgetFromName(TEXT("StartButton")));

	mStartButton->OnClicked.AddDynamic(this, &UCharacterSelectWidget::StartButtonClick);
}

void UCharacterSelectWidget::StartButtonClick()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("NewMap"));
}
