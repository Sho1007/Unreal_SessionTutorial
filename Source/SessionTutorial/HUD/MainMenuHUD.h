// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
class UMainMenuWidget;
UCLASS()
class SESSIONTUTORIAL_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	void TearDown();

	void SetServerList(const TArray<FOnlineSessionSearchResult>& SearchResults);
private:
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;
	UMainMenuWidget* MainMenuWidget;
};