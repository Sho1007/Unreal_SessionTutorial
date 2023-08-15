// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include <OnlineSubsystem.h>
#include <Interfaces/OnlineSessionInterface.h>

#include "Interface/MainMenuInterface.h"

#include "MyGameInstance.generated.h"

/**
 *
 */
class FOnlineSessionSearch;
UCLASS()
class SESSIONTUTORIAL_API UMyGameInstance : public UGameInstance, public IMainMenuInterface
{
	GENERATED_BODY()

public:
	UMyGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init() override;

	// Inherited via IMainMenuInterface
	virtual void Host() override;
	virtual void Join(uint32 Index) override;
	virtual void LoadMainMenu() override;
	virtual void FindSession() override;

private:
	void CreateSession();
	void OnCreateSessionComplete(FName SessionName, bool bSuccessed);
	void OnDestroySessionComplete(FName SessionName, bool bSuccessed);
	void OnFindSessionsComplete(bool bSuccessed);
	void OnJoinSessionsComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
};