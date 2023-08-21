// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
class UButton;
class IMainMenuInterface;
class UWidgetSwitcher;
class UEditableText;
class UScrollBox;
class UServerListSlotWidget;
class UCircularThrobber;
UCLASS()
class SESSIONTUTORIAL_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;
	void Setup();
	void Teardown();

	void SetMainMenuInterface(IMainMenuInterface* NewMainMenuInterface);

	void SetServerList(const TArray<FOnlineSessionSearchResult>& SearchResults);

	void SelectIndex(uint32 Index);

private:
	UFUNCTION()
	void OnClickedHostMenuButton();
	UFUNCTION()
	void OnClickedJoinMenuButton();
	UFUNCTION()
	void OnClickedQuitButton();

	UFUNCTION()
	void OnClickedHostButton();

	UFUNCTION()
	void OnClickedConnectButton();
	UFUNCTION()
	void OnClickedCancelButton();
	
private:
	// MainMenu
	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_HostMenu;
	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_JoinMenu;
	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Quit;
	// HostMenu
	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UEditableText* ET_ServerName;
	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Host;
	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_CancelFromHostMenu;
	// JoinMenu
	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Connect;
	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Cancel;
	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UScrollBox* ServerList;
	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UCircularThrobber* Throbber;

	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	TSubclassOf<UServerListSlotWidget> ServerListSlotWidgetClass;

	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UWidgetSwitcher* WS_ChangeMenu;


	IMainMenuInterface* MainMenuInterface;

	TOptional<uint32> SelectedIndex;
};