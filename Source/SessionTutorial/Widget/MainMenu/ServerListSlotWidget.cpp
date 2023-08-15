// Fill out your copyright notice in the Description page of Project Settings.


#include "../MainMenu/ServerListSlotWidget.h"

#include <Components/TextBlock.h>
#include <Components/Button.h>

#include "MainMenuWidget.h"

void UServerListSlotWidget::Setup(UMainMenuWidget* NewParentWidget, uint32 NewIndex)
{
	Parent = NewParentWidget;
	Index = NewIndex;
}

void UServerListSlotWidget::SetServerName(FText NewServerName)
{
	ServerName->SetText(NewServerName);
}

bool UServerListSlotWidget::Initialize()
{
	if (Super::Initialize() == false) return false;

	Button->OnClicked.AddDynamic(this, &UServerListSlotWidget::OnClicked);

	return true;
}

void UServerListSlotWidget::OnClicked()
{
	if (Parent && IsValid(Parent))
	{
		Parent->SelectIndex(Index);
	}
}