// Fill out your copyright notice in the Description page of Project Settings.


#include "../HUD/BattleHUD.h"

#include "../Widget/InGameMenu/InGameMenuWidget.h"

void ABattleHUD::TearDown()
{
	if (InGameMenuWidget)
	{
		InGameMenuWidget->TearDown();
	}
}

void ABattleHUD::ToggleInGameMenu()
{
	InGameMenuWidget->GetVisibility() == ESlateVisibility::Visible ? InGameMenuWidget->TearDown() : InGameMenuWidget->Setup();
}

void ABattleHUD::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(InGameMenuWidgetClass))
	{
		InGameMenuWidget = CreateWidget<UInGameMenuWidget>(GetOwningPlayerController(), InGameMenuWidgetClass, TEXT("InGameMenuWidget"));
		check(InGameMenuWidget);
		InGameMenuWidget->TearDown();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ABattleHUD::BeginPlay : InGameMenuWidgetClass is Not Valid"));
	}
}
