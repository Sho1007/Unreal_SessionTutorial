// Fill out your copyright notice in the Description page of Project Settings.

#include "../MainMenu/MainMenuWidget.h"

#include <Components/Button.h>
#include <Components/WidgetSwitcher.h>
#include <Components/EditableText.h>
#include <Components/ScrollBox.h>
#include <Components/CircularThrobber.h>
#include <GameFramework/GameState.h>
#include <Kismet/KismetSystemLibrary.h>
#include <OnlineSessionSettings.h>

#include "../../Interface/MainMenuInterface.h"
#include "../../MyGameInstance.h"
#include "ServerListSlotWidget.h"

bool UMainMenuWidget::Initialize()
{
	if (!Super::Initialize()) return false;

	Btn_Host->OnClicked.AddDynamic(this, &UMainMenuWidget::OnClickedHostButton);
	Btn_Join->OnClicked.AddDynamic(this, &UMainMenuWidget::OnClickedJoinButton);
	Btn_Quit->OnClicked.AddDynamic(this, &UMainMenuWidget::OnClickedQuitButton);

	Btn_Connect->OnClicked.AddDynamic(this, &UMainMenuWidget::OnClickedConnectButton);
	Btn_Cancle->OnClicked.AddDynamic(this, &UMainMenuWidget::OnClickedCancleButton);

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

		this->RemoveFromParent();
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

void UMainMenuWidget::SetServerList(const TArray<FOnlineSessionSearchResult>& SearchResults)
{
	Throbber->SetVisibility(ESlateVisibility::Collapsed);
	if (ServerListSlotWidgetClass && IsValid(ServerListSlotWidgetClass))
	{
		for (int i = 0; i < SearchResults.Num(); ++i)
		{
			UServerListSlotWidget* NewChildWidget = CreateWidget<UServerListSlotWidget>(this, ServerListSlotWidgetClass);
			NewChildWidget->Setup(this, i);
			NewChildWidget->SetServerName(FText::FromString(SearchResults[i].GetSessionIdStr()));
			NewChildWidget->SetHostUser(FText::FromString(SearchResults[i].Session.OwningUserName));
			NewChildWidget->SetCurrentPlayerCount(SearchResults[i].Session.NumOpenPublicConnections);
			NewChildWidget->SetMaxPlayerCount(SearchResults[i].Session.SessionSettings.NumPublicConnections);

			ServerList->AddChild(NewChildWidget);
		}
	}	
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UMainMenuWidget::SetServerList : ServerListSlotWidgetClass is Invalid"));
	}
}

void UMainMenuWidget::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;

	for (int i = 0; i < ServerList->GetChildrenCount(); ++i)
	{
		if (i == Index) continue;
		if (UServerListSlotWidget* ServerListSlot = Cast<UServerListSlotWidget>(ServerList->GetChildAt(i)))
		{
			ServerListSlot->SetUnclicked();
		}
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
	ServerList->ClearChildren();
	Throbber->SetVisibility(ESlateVisibility::Visible);
	MainMenuInterface->FindSession();
	SelectedIndex.Reset();

	WS_ChangeMenu->SetActiveWidgetIndex(1);
}

void UMainMenuWidget::OnClickedConnectButton()
{
	if (SelectedIndex.IsSet())
	{
		UE_LOG(LogTemp, Warning, TEXT("UMainMenuWidget::OnClickedConnectButton : Selected Index : %d"), SelectedIndex.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UMainMenuWidget::OnClickedConnectButton : Index is Not Selected"));
	}
	if (MainMenuInterface)
	{
		MainMenuInterface->Join(SelectedIndex.GetValue());
	}
}

void UMainMenuWidget::OnClickedCancleButton()
{
	// Clear Text
	//ET_IPAddress->SetText(FText());

	WS_ChangeMenu->SetActiveWidgetIndex(0);
}

void UMainMenuWidget::OnClickedQuitButton()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);
}