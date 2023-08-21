// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include <OnlineSessionSettings.h>

#include "GameMode/MainMenuGameMode.h"
#include "HUD/MainMenuHUD.h"
#include "HUD/BattleHUD.h"

UMyGameInstance::UMyGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UMyGameInstance::Init()
{
	Super::Init();

	if (IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		UE_LOG(LogTemp, Warning, TEXT("UMyGameInstance::Init : Found OnlineSubsystem : %s"), *Subsystem->GetSubsystemName().ToString());
		if (SessionInterface = Subsystem->GetSessionInterface())
		{
			UE_LOG(LogTemp, Warning, TEXT("UMyGameInstance::Init : Found Session Interface"));
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UMyGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UMyGameInstance::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UMyGameInstance::OnFindSessionsComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UMyGameInstance::OnJoinSessionsComplete);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UMyGameInstance::Init : OnlineSubsystem is Not Valid"));
	}
}

void UMyGameInstance::Host(FString NewServerName)
{
	if (SessionInterface.IsValid())
	{
		ServerName = NewServerName;
		FNamedOnlineSession* Session = SessionInterface->GetNamedSession(EName::GameSession);
		if (Session != nullptr)
		{
			SessionInterface->DestroySession(EName::GameSession);
		}
		else
		{
			CreateSession();
		}
	}
}

void UMyGameInstance::Join(uint32 Index)
{
	if (!SessionInterface.IsValid()) return;
	if (!SessionSearch.IsValid()) return;

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
				SessionInterface->JoinSession(0, EName::GameSession, SessionSearch->SearchResults[Index]);
			}
		}
	}	
}

void UMyGameInstance::LoadMainMenu()
{
	if (GEngine)
	{
		if (UWorld* World = GetWorld())
		{
			if (APlayerController* PlayerController = World->GetFirstPlayerController())
			{
				if (ABattleHUD* HUD = PlayerController->GetHUD<ABattleHUD>())
				{
					HUD->TearDown();
				}
				PlayerController->ClientTravel("/Game/Levels/L_MainMenu", TRAVEL_Absolute);
			}
		}
	}
}

void UMyGameInstance::CreateSession()
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings SessionSettings;	

		if (IOnlineSubsystem::Get()->GetSubsystemName() == TEXT("NULL"))
		{
			SessionSettings.bIsLANMatch = true;
		}
		else
		{
			SessionSettings.bIsLANMatch = false; // Is LAN Connection?
		}
		SessionSettings.NumPublicConnections = 3; // How many Connection
		SessionSettings.bShouldAdvertise = true;
		SessionSettings.bUsesPresence = true;
		SessionSettings.Set(TEXT("SessionName"), ServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
		//SessionSettings.bUseLobbiesIfAvailable = true;

		SessionInterface->CreateSession(0, EName::GameSession, SessionSettings);
	}
}

void UMyGameInstance::OnCreateSessionComplete(FName SessionName, bool bSuccessed)
{
	if (bSuccessed == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("UMyGameInstance::OnCreateSessionComplete : Failed to Create Session"));
		return;
	}

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

			World->ServerTravel(TEXT("/Game/Levels/L_Lobby?listen"));
		}
	}
}

void UMyGameInstance::OnDestroySessionComplete(FName SessionName, bool bSuccessed)
{
	if (bSuccessed == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("UMyGameInstance::OnCreateSessionComplete : Failed to Destroy Session"));
		return;
	}

	CreateSession();
}

void UMyGameInstance::FindSession()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("UMyGameInstance::Init : Starting Find Session"));

		if (IOnlineSubsystem::Get()->GetSubsystemName() == TEXT("NULL"))
		{
			SessionSearch->bIsLanQuery = true;
		}
		else
		{
			SessionSearch->bIsLanQuery = false;
		}
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		SessionSearch->MaxSearchResults = 100;
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

void UMyGameInstance::StartSession()
{
	SessionInterface->StartSession(EName::GameSession);
}

void UMyGameInstance::OnFindSessionsComplete(bool bSuccessed)
{
	if (SessionSearch.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("UMyGameInstance::OnFindSessionsComplete : Find Session Finished : %d"), SessionSearch->SearchResults.Num());

		if (UWorld* World = GetWorld())
		{
			if (APlayerController* PlayerController = World->GetFirstPlayerController())
			{
				if (AMainMenuHUD* HUD = PlayerController->GetHUD<AMainMenuHUD>())
				{
					HUD->SetServerList(SessionSearch->SearchResults);
				}
			}
		}
		for (const FOnlineSessionSearchResult& SessionSearchResult : SessionSearch->SearchResults)
		{
			if (SessionSearchResult.IsValid())
			{
				UE_LOG(LogTemp, Warning, TEXT("Found Session Name : %s"), *SessionSearchResult.Session.SessionInfo->ToString());
			}
		}
	}
}

void UMyGameInstance::OnJoinSessionsComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (UEngine* Engine = GetEngine())
	{
		if (APlayerController* PlayerController = GetFirstLocalPlayerController())
		{
			FString Address;
			if (SessionInterface->GetResolvedConnectString(SessionName, Address) == false)
			{
				UE_LOG(LogTemp, Warning, TEXT("UMyGameInstance::OnJoinSessionsComplete : Could Not Get Connect String."));
				return;
			}


			PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("Session Name : %s"), *SessionName.ToString());
}