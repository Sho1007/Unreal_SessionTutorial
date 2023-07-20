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
UCLASS()
class SESSIONTUTORIAL_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;
	void Setup();
	void Teardown();

	void SetMainMenuInterface(IMainMenuInterface* NewMainMenuInterface);

private:
	UFUNCTION()
	void OnClickedHostButton();
	UFUNCTION()
	void OnClickedJoinButton();
	
private:
	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Host;
	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Join;

	IMainMenuInterface* MainMenuInterface;
};