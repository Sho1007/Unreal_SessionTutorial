// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

/**
 * 
 */
//class UMainMenuWidget;
UCLASS()
class SESSIONTUTORIAL_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
private:
	//UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	//TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;
	//UMainMenuWidget* MainMenuWidget;
};
