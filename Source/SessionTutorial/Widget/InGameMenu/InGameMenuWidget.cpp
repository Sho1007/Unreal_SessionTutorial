// Fill out your copyright notice in the Description page of Project Settings.


#include "../InGameMenu/InGameMenuWidget.h"

#include <Components/Button.h>

#include "../../Interface/MainMenuInterface.h"

void UInGameMenuWidget::Setup()
{
	UE_LOG(LogTemp, Log, TEXT("UInGameMenuWidget::Setup Called"));
	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		this->AddToViewport();
		PlayerController->SetInputMode(FInputModeGameAndUI());
		PlayerController->SetShowMouseCursor(true);
		this->SetVisibility(ESlateVisibility::Visible);
	}
}

void UInGameMenuWidget::TearDown()
{
	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		this->RemoveFromViewport();
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->SetShowMouseCursor(false);
		this->SetVisibility(ESlateVisibility::Collapsed);
	}
}

bool UInGameMenuWidget::Initialize()
{
	if (Super::Initialize() == false) return false;

	Btn_Quit->OnClicked.AddDynamic(this, &UInGameMenuWidget::OnClickedQuitButton);
	Btn_Cancle->OnClicked.AddDynamic(this, &UInGameMenuWidget::OnClickedCancleButton);

	return true;
}

void UInGameMenuWidget::OnClickedQuitButton()
{
	if (IMainMenuInterface* Interface = Cast<IMainMenuInterface>(GetGameInstance()))
	{
		Interface->LoadMainMenu();
	}
}

void UInGameMenuWidget::OnClickedCancleButton()
{
	this->TearDown();
}