// Fill out your copyright notice in the Description page of Project Settings.


#include "../InGameMenu/InGameMenuWidget.h"

#include <Components/Button.h>

void UInGameMenuWidget::Setup()
{
	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		PlayerController->SetInputMode(FInputModeGameAndUI());
		PlayerController->SetShowMouseCursor(true);
		this->SetVisibility(ESlateVisibility::Visible);
	}
}

void UInGameMenuWidget::TearDown()
{
	if (APlayerController* PlayerController = GetOwningPlayer())
	{
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
	if (UWorld* World = GetWorld())
	{
		World->ClientTravel(TEXT("/Game/Levels/L_MainMenu"));
	}
}

void UInGameMenuWidget::OnClickedCancleButton()
{
	this->Hide();
}