#pragma once

#include "../SessionTutorialCharacter.h"
#include <UObject/Interface.h>
#include "MainMenuInterface.generated.h"

UINTERFACE(MinimalAPI)
class UMainMenuInterface : public UInterface
{
	GENERATED_BODY()
};

class SESSIONTUTORIAL_API IMainMenuInterface
{
	GENERATED_BODY()
public:
	virtual void Join(uint32 Index) = 0;
	virtual void Host(FString NewServerName) = 0;
	virtual void LoadMainMenu() = 0;
	virtual void FindSession() = 0;
};