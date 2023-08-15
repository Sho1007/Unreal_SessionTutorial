// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerListSlotWidget.generated.h"

/**
 * 
 */
class UMainMenuWidget;
class UTextBlock;
class UButton;
UCLASS()
class SESSIONTUTORIAL_API UServerListSlotWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void Setup(UMainMenuWidget* NewParentWidget, uint32 NewIndex);

	void SetServerName(FText NewServerName);
	void SetUnclicked();

protected:
	virtual bool Initialize() override;

private:
	UFUNCTION()
	virtual void OnClicked();
	UFUNCTION()
	virtual void OnHovered();
	UFUNCTION()
	virtual void OnUnhovered();
private:
	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Button;
	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* ServerName;

	UMainMenuWidget* Parent;
	uint32 Index;

	bool bIsClicked = false;
};