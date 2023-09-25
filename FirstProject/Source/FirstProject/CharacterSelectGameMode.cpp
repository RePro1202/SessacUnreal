// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectGameMode.h"
#include "UI/CharacterSelectWidget.h"

ACharacterSelectGameMode::ACharacterSelectGameMode()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/UI_CharacterSelect.UI_CharacterSelect_C'"));
	if (WidgetClass.Succeeded())
		mUIClass = WidgetClass.Class;

	DefaultPawnClass = nullptr;
}

void ACharacterSelectGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void ACharacterSelectGameMode::InitGameState()
{
	Super::InitGameState();
}

void ACharacterSelectGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	NewPlayer->SetShowMouseCursor(true);

	FInputModeUIOnly input;
	NewPlayer->SetInputMode(input);
}

void ACharacterSelectGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(mUIClass))
	{
		mWidget = CreateWidget<UCharacterSelectWidget>(GetWorld(), mUIClass);

		if (IsValid(mWidget))
			mWidget->AddToViewport();
	}
}

void ACharacterSelectGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
