// Fill out your copyright notice in the Description page of Project Settings.


#include "../Character/BattleCharacter.h"

#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include <InputMappingContext.h>

#include "../HUD/BattleHUD.h"

// Sets default values
ABattleCharacter::ABattleCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ABattleCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(DefaultContext))
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(DefaultContext, 0);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ABattleCharacter::BeginPlay : DefaultContext is not Valid"));
	}
}

// Called every frame
void ABattleCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABattleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (IsValid(MoveAction))
		{
			Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABattleCharacter::Move);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("ABattleCharacter::SetupPlayerInputComponent : MoveAction is not Valid"));
		}
		if (IsValid(LookAction))
		{
			Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABattleCharacter::Look);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("ABattleCharacter::SetupPlayerInputComponent : LookAction is not Valid"));
		}
		if (IsValid(InGameMenuAction))
		{
			Input->BindAction(InGameMenuAction, ETriggerEvent::Started, this, &ABattleCharacter::InGameMenuPressed);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("ABattleCharacter::SetupPlayerInputComponent : InGameMenuAction is not Valid"));
		}
	}
}

void ABattleCharacter::Move(const FInputActionInstance& Instance)
{
	FVector2D Value = Instance.GetValue().Get<FVector2D>();
	//UE_LOG(LogTemp, Warning, TEXT("ABattleCharacter::Move : %s"), *Value.ToString());

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		FRotator Rotation = GetControlRotation();
		FRotator YawRotation(0, Rotation.Yaw, 0);

		AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X), Value.Y);
		AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y), Value.X);
	}
}

void ABattleCharacter::Look(const FInputActionInstance& Instance)
{
	FVector2D Value = Instance.GetValue().Get<FVector2D>();
	//UE_LOG(LogTemp, Warning, TEXT("ABattleCharacter::Look : %s"), *Value.ToString());

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		PC->AddPitchInput(-Value.Y);
		PC->AddYawInput(Value.X);
	}
}

void ABattleCharacter::InGameMenuPressed(const FInputActionInstance& Instance)
{
	UE_LOG(LogTemp, Warning, TEXT("ABattleCharacter::InGameMenuPressed : Called"));

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (ABattleHUD* HUD = PC->GetHUD<ABattleHUD>())
		{
			HUD->ToggleInGameMenu();
		}
	}
}