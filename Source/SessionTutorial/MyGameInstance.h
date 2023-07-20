// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "Interface/MainMenuInterface.h"

#include "MyGameInstance.generated.h"

/**
 *
 */
UCLASS()
class SESSIONTUTORIAL_API UMyGameInstance : public UGameInstance, public IMainMenuInterface
{
	GENERATED_BODY()

public:
	UMyGameInstance(const FObjectInitializer& ObjectInitializer);

	// Inherited via IMainMenuInterface
	virtual void Host() override;
	virtual void Join() override;
};