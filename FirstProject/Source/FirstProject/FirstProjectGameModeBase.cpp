// Copyright Epic Games, Inc. All Rights Reserved.


#include "FirstProjectGameModeBase.h"
#include "Player/MagicianCharacter.h"
#include "Player/SAC1PlayerState.h"
#include "SAC1GameState.h"
#include "Player/SACPlayerController.h"
#include "AI/AIPawn.h"
#include "UI/MainWidget.h"

AFirstProjectGameModeBase::AFirstProjectGameModeBase()
{
	// 클래스 레퍼런스 에셋을 불러오고자 할 경우 에셋의 경로에서 가장 마지막에 _C를 반드시 붙여줘야 한다.
	static ConstructorHelpers::FClassFinder<ACharacter> BlueprintPawn(TEXT("/Script/Engine.Blueprint'/Game/TestBlueprint/TestPlayer.TestPlayer_C'"));

	if (BlueprintPawn.Succeeded())
	{
		DefaultPawnClass = BlueprintPawn.Class;
	}

	// AMagicianCharacter::StaticClass() : AMagicianCharacter 클래스의 클래스 레퍼런스를 얻어온다.
	// cpp클래스는 블루프린트와 달리 로드 없이 가져올 수 있다.
	DefaultPawnClass = AMagicianCharacter::StaticClass();

	// PlayerStateClass를 지정한다.
	PlayerStateClass = ASAC1PlayerState::StaticClass();

	GameStateClass = ASAC1GameState::StaticClass();

	PlayerControllerClass = ASACPlayerController::StaticClass();

	static ConstructorHelpers::FClassFinder<UUserWidget> MainUIClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/UI_Main.UI_Main_C'"));
	if (MainUIClass.Succeeded())
		mMainUIClass = MainUIClass.Class;

}

void AFirstProjectGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AFirstProjectGameModeBase::InitGameState()
{
	Super::InitGameState();
}

void AFirstProjectGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	// auto : 대입받는 값의 타입을 자동으로 결정한다.
	auto PlayerState = NewPlayer->GetPlayerState<ASAC1PlayerState>();

	if (IsValid(PlayerState))
		PlayerState->InitPlayerData(EPlayerJob::Magicion);
}

void AFirstProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(mMainUIClass))
	{
		mMainWidget = CreateWidget<UMainWidget>(GetWorld(), mMainUIClass);

		if (IsValid(mMainWidget))
			mMainWidget->AddToViewport();
	}
}

void AFirstProjectGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
