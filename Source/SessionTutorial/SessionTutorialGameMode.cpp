// Copyright Epic Games, Inc. All Rights Reserved.

#include "SessionTutorialGameMode.h"
#include "SessionTutorialCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASessionTutorialGameMode::ASessionTutorialGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
