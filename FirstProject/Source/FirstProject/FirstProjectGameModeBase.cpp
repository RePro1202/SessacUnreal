// Copyright Epic Games, Inc. All Rights Reserved.


#include "FirstProjectGameModeBase.h"
#include "Player/MagicianCharacter.h"
#include "Player/SAC1PlayerState.h"
#include "SAC1GameState.h"
#include "AI/AIPawn.h"

AFirstProjectGameModeBase::AFirstProjectGameModeBase()
{
	// Ŭ���� ���۷��� ������ �ҷ������� �� ��� ������ ��ο��� ���� �������� _C�� �ݵ�� �ٿ���� �Ѵ�.
	static ConstructorHelpers::FClassFinder<ACharacter> BlueprintPawn(TEXT("/Script/Engine.Blueprint'/Game/TestBlueprint/TestPlayer.TestPlayer_C'"));

	if (BlueprintPawn.Succeeded())
	{
		DefaultPawnClass = BlueprintPawn.Class;
	}

	// AMagicianCharacter::StaticClass() : AMagicianCharacter Ŭ������ Ŭ���� ���۷����� ���´�.
	// cppŬ������ �������Ʈ�� �޸� �ε� ���� ������ �� �ִ�.
	DefaultPawnClass = AMagicianCharacter::StaticClass();

	// PlayerStateClass�� �����Ѵ�.
	PlayerStateClass = ASAC1PlayerState::StaticClass();

	GameStateClass = ASAC1GameState::StaticClass();
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

	// auto : ���Թ޴� ���� Ÿ���� �ڵ����� �����Ѵ�.
	auto PlayerState = NewPlayer->GetPlayerState<ASAC1PlayerState>();

	if (IsValid(PlayerState))
		PlayerState->InitPlayerData(EPlayerJob::Magicion);
}

void AFirstProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AFirstProjectGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
