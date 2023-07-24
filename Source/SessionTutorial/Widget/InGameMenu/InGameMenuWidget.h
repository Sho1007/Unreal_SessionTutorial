// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameMenuWidget.generated.h"

/**
 * 
 */
class UButton;
UCLASS()
class SESSIONTUTORIAL_API UInGameMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Setup();
	void TearDown();
protected:
	virtual bool Initialize() override;
private:

	UFUNCTION()
	void OnClickedQuitButton();
	UFUNCTION()
	void OnClickedCancleButton();
private:
	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Quit;

	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Cancle;
};
