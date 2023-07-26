// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BattleCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionInstance;
UCLASS()
class SESSIONTUTORIAL_API ABattleCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABattleCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void Move(const FInputActionInstance& Instance);
	void Look(const FInputActionInstance& Instance);
	void InGameMenuPressed(const FInputActionInstance& Instance);

private:
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	UCameraComponent* CameraComponent;

	// InputAction
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	UInputAction* MoveAction;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	UInputAction* LookAction;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	UInputAction* InGameMenuAction;
	
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	UInputMappingContext* DefaultContext;
};