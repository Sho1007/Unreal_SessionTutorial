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

void UServerListSlotWidget::SetUnclicked()
{
	bIsClicked = false;
	ServerName->SetColorAndOpacity(FLinearColor(1, 1, 1, 1));
}

bool UServerListSlotWidget::Initialize()
{
	if (Super::Initialize() == false) return false;

	Button->OnClicked.AddDynamic(this, &UServerListSlotWidget::OnClicked);
	Button->OnHovered.AddDynamic(this, &UServerListSlotWidget::OnHovered);
	Button->OnUnhovered.AddDynamic(this, &UServerListSlotWidget::OnUnhovered);

	return true;
}

void UServerListSlotWidget::OnClicked()
{
	if (Parent && IsValid(Parent))
	{
		bIsClicked = true;
		ServerName->SetColorAndOpacity(FLinearColor(0, 1, 0, 1));
		Parent->SelectIndex(Index);
	}
}

void UServerListSlotWidget::OnHovered()
{
	ServerName->SetColorAndOpacity(FLinearColor(1, 1, 0, 1));
}

void UServerListSlotWidget::OnUnhovered()
{
	if (bIsClicked == false) ServerName->SetColorAndOpacity(FLinearColor(1, 1, 1, 1));
}