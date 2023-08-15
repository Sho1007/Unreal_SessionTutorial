// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include <OnlineSessionSettings.h>

#include "GameMode/MainMenuGameMode.h"
#include "HUD/MainMenuHUD.h"
#include "HUD/BattleHUD.h"

static const FName SESSION_NAME = TEXT("My Session Game");

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

void UMyGameInstance::Host()
{
	if (SessionInterface.IsValid())
	{
		FNamedOnlineSession* Session = SessionInterface->GetNamedSession(SESSION_NAME);
		if (Session != nullptr)
		{
			SessionInterface->DestroySession(SESSION_NAME);
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

				SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[Index]);
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
		SessionSettings.bIsLANMatch = false; // Is LAN Connection?
		SessionSettings.NumPublicConnections = 2; // How many Connection
		SessionSettings.bShouldAdvertise = true;
		SessionSettings.bUsesPresence = true;
		SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
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

			World->ServerTravel(TEXT("/Game/Levels/L_Laboratory?listen"));
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
		//SessionSearch->bIsLanQuery = true;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		SessionSearch->MaxSearchResults = 100;
		// SessionSearch->QuerySettings.Set(); Setting Depends on API what is used
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

void UMyGameInstance::OnFindSessionsComplete(bool bSuccessed)
{
	if (bSuccessed && SessionSearch.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("UMyGameInstance::OnFindSessionsComplete : Find Session Finished"));

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

	UE_LOG(LogTemp, Warning, TEXT("Session Name : %s"), *SessionName.ToString());
}