// Copyright Epic Games, Inc. All Rights Reserved.


#include "FirstProjectGameModeBase.h"
#include "Player/MagicianCharacter.h"
#include "Player/SAC1PlayerState.h"

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
}
