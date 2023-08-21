// Fill out your copyright notice in the Description page of Project Settings.


#include "../GameMode/LobbyGameMode.h"
#include "../MyGameInstance.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (++NumberOfPlayers == 3)
	{
		if (UWorld* World = GetWorld())
		{
			if (!ServerTravelTimerHandle.IsValid())
			{
				UE_LOG(LogTemp, Warning, TEXT("ALobbyGameMode::PostLogin : Timer Started"));
				World->GetTimerManager().SetTimer(ServerTravelTimerHandle, this, &ALobbyGameMode::ServerTravel, 10.0f, false);
			}
		}
	}	
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	NumberOfPlayers--;
}

void ALobbyGameMode::ServerTravel()
{
	if (UWorld* World = GetWorld())
	{
		if (UMyGameInstance* GameInstance = GetGameInstance<UMyGameInstance>())
		{
			GameInstance->StartSession();
			bUseSeamlessTravel = true;
			World->ServerTravel(TEXT("/Game/Levels/L_Laboratory?listen"));
		}
		else UE_LOG(LogTemp, Error, TEXT("ALobbyGameMode::ServerTravel : GameInstance is Invalid"));
	}
	else UE_LOG(LogTemp, Error, TEXT("ALobbyGameMode::ServerTravel : World is Invalid"));
}