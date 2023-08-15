// Fill out your copyright notice in the Description page of Project Settings.


#include "../HUD/MainMenuHUD.h"

#include "../Widget/MainMenu/MainMenuWidget.h"

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(GetOwningPlayerController()))
	{
		check(MainMenuWidgetClass);
		MainMenuWidget = CreateWidget<UMainMenuWidget>(GetOwningPlayerController(), MainMenuWidgetClass, TEXT("MainMenuWidget"));
		check(MainMenuWidget);
		MainMenuWidget->Setup();
	}
}

void AMainMenuHUD::TearDown()
{
	MainMenuWidget->Teardown();
}

void AMainMenuHUD::SetServerList(const TArray<FOnlineSessionSearchResult>& SearchResults)
{
	MainMenuWidget->SetServerList(SearchResults);
}