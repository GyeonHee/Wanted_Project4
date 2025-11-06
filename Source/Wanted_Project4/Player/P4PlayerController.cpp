// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/P4PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "Character/P4CharacterPlayer.h"

AP4PlayerController::AP4PlayerController()
{
	//bShowMouseCursor = false;
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> DefaultMappingRef(TEXT("/Game/Character/Input/IMC_Default.IMC_Default"));
	if (DefaultMappingRef.Succeeded())
	{
		InputMappingContext = DefaultMappingRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionRef(TEXT("/Game/Character/Input/Action/IA_Move.IA_Move"));
	if (MoveActionRef.Succeeded())
	{
		MoveAction = MoveActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> LookActionRef(TEXT("/Game/Character/Input/Action/IA_Look.IA_Look"));
	if (LookActionRef.Succeeded())
	{
		LookAction = LookActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> JumpActionRef(TEXT("/Game/Character/Input/Action/IA_Jump.IA_Jump"));
	if (JumpActionRef.Succeeded())
	{
		JumpAction = JumpActionRef.Object;
	}

	//static ConstructorHelpers::FObjectFinder<UInputAction> AttackActionRef(TEXT("/Game/ArenaBattle/Input/Actions/IA_Attack.IA_Attack"));
	//if (AttackActionRef.Succeeded())
	//{
	//	AttackAction = AttackActionRef.Object;
	//}
}

void AP4PlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Change input mode
	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);

	// todo: need to change for other menus such as Pause, Inventory etc.
	//FInputModeUIOnly
	//FInputModeGameAndUI


	// Enhanced Input Subsystem 초기화
	if (InputMappingContext)
	{
		if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem =
				ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
			{
				InputSystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}

	ConsoleCommand(TEXT("showdebug abilitysystem"));

}

void AP4PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AP4PlayerController::HandleMove);
		EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &AP4PlayerController::HandleLook);
		EIC->BindAction(JumpAction, ETriggerEvent::Started, this, &AP4PlayerController::HandleJumpStart);
		EIC->BindAction(JumpAction, ETriggerEvent::Completed, this, &AP4PlayerController::HandleJumpEnd);

		//EIC->BindAction(AttackAction, ETriggerEvent::Started, this, &AP4PlayerController::HandleAttack);
	}
}

void AP4PlayerController::HandleMove(const FInputActionValue& Value)
{
	if (AP4CharacterPlayer* CharacterPlayer = Cast<AP4CharacterPlayer>(GetPawn()))
	{
		CharacterPlayer->HandleMove(Value);
	}
}

void AP4PlayerController::HandleLook(const FInputActionValue& Value)
{
	if (AP4CharacterPlayer* CharacterPlayer = Cast<AP4CharacterPlayer>(GetPawn()))
	{
		CharacterPlayer->HandleLook(Value);
	}
}

void AP4PlayerController::HandleJumpStart(const FInputActionValue& Value)
{
	if (AP4CharacterPlayer* CharacterPlayer = Cast<AP4CharacterPlayer>(GetPawn()))
	{
		CharacterPlayer->Jump();
	}
}

void AP4PlayerController::HandleJumpEnd(const FInputActionValue& Value)
{
	if (AP4CharacterPlayer* CharacterPlayer = Cast<AP4CharacterPlayer>(GetPawn()))
	{
		CharacterPlayer->StopJumping();
	}
}

//void AP4PlayerController::HandleAttack(const FInputActionValue& Value)
//{
//	if (AP4CharacterPlayer* CharacterPlayer = Cast<AP4CharacterPlayer>(GetPawn()))
//	{
//		CharacterPlayer->HandleAttack(Value);
//	}
//}