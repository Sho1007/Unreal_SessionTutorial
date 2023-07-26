// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BattleHUD.generated.h"

/**
 * 
 */
class UInGameMenuWidget;
UCLASS()
class SESSIONTUTORIAL_API ABattleHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	void TearDown();

	void ToggleInGameMenu();
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPirvateAccess = true))
	TSubclassOf<UInGameMenuWidget> InGameMenuWidgetClass;
	UInGameMenuWidget* InGameMenuWidget;
};