// Copyright Epic Games, Inc. All Rights Reserved.


#include "FirstProjectGameModeBase.h"
#include "Player/MagicianCharacter.h"

AFirstProjectGameModeBase::AFirstProjectGameModeBase()
{
	// 클래스 레퍼런스 에셋을 불러오고자 할 경우 에셋의 경로에서 가장 마지막에 _C를 반드시 붙여줘야 한다.
	static ConstructorHelpers::FClassFinder<ACharacter> BlueprintPawn(TEXT("/Script/Engine.Blueprint'/Game/TestBlueprint/TestPlayer.TestPlayer_C'"));

	if (BlueprintPawn.Succeeded())
	{
		DefaultPawnClass = BlueprintPawn.Class;
	}
}
