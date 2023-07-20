// Fill out your copyright notice in the Description page of Project Settings.

#include "../MainMenu/MainMenuWidget.h"

#include <Components/Button.h>
#include <GameFramework/GameState.h>

#include "../../Interface/MainMenuInterface.h"
#include "../../MyGameInstance.h"

bool UMainMenuWidget::Initialize()
{
	if (!Super::Initialize()) return false;

	Btn_Host->OnClicked.AddDynamic(this, &UMainMenuWidget::OnClickedHostButton);
	Btn_Join->OnClicked.AddDynamic(this, &UMainMenuWidget::OnClickedJoinButton);

	return true;
}

void UMainMenuWidget::Setup()
{
	if (IsValid(GetOwningPlayer()))
	{
		this->AddToViewport();
		this->SetMainMenuInterface(GetGameInstance<UMyGameInstance>());

		GetOwningPlayer()->SetShowMouseCursor(true);
		GetOwningPlayer()->SetInputMode(FInputModeUIOnly());
	}
}

void UMainMenuWidget::Teardown()
{
	if (IsValid(GetOwningPlayer()))
	{
		GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
		GetOwningPlayer()->SetShowMouseCursor(false);

		this->RemoveFromViewport();
	}
}

void UMainMenuWidget::SetMainMenuInterface(IMainMenuInterface* NewMainMenuInterface)
{
	if (NewMainMenuInterface)
	{
		this->MainMenuInterface = NewMainMenuInterface;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UMainMenuWidget::SetMainMenuInterface : NewMainMenuInterface is Not Valid"));
	}
}

void UMainMenuWidget::OnClickedHostButton()
{
	if (MainMenuInterface)
	{
		MainMenuInterface->Host();
	}
}

void UMainMenuWidget::OnClickedJoinButton()
{
	if (MainMenuInterface)
	{
		MainMenuInterface->Join();
	}
}