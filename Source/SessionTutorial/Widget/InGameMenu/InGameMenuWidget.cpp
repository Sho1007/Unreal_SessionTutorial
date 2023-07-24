// Fill out your copyright notice in the Description page of Project Settings.


#include "../InGameMenu/InGameMenuWidget.h"

#include <Components/Button.h>

void UInGameMenuWidget::Setup()
{
	this->AddToViewport();
	this->SetVisibility(ESlateVisibility::Collapsed);

	/*if (APlayerController* PlayerController = GetOwningPlayer())
	{
		
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UInGameMenuWidget::Setup : OwningPlayer is not Valid"));
	}*/
}

void UInGameMenuWidget::TearDown()
{
	this->RemoveFromViewport();

	/*if (APlayerController* PlayerController = GetOwningPlayer())
	{
		
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UInGameMenuWidget::TearDown : OwningPlayer is not Valid"));
	}*/
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
		World->ServerTravel(TEXT("/Game/Levels/L_MainMenu"));
	}
}

void UInGameMenuWidget::OnClickedCancleButton()
{
	this->SetVisibility(ESlateVisibility::Collapsed);
}