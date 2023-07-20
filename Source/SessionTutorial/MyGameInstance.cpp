// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "GameMode/MainMenuGameMode.h"
#include "HUD/MainMenuHUD.h"

UMyGameInstance::UMyGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UMyGameInstance::Host()
{
	if (GEngine)
	{
		if (UWorld* World = GetWorld())
		{
			if (APlayerController* PlayerController = World->GetFirstPlayerController())
			{
				if (AMainMenuHUD* HUD = PlayerController->GetHUD<AMainMenuHUD>())
				{
					HUD->TearDown();
				}
			}

			World->ServerTravel(TEXT("/Game/Levels/L_Laboratory?listen"));
		}
	}
}

void UMyGameInstance::Join()
{
}