// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/P4PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "Character/P4CharacterPlayer.h"
#include "AbilitySystemComponent.h"

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

	static ConstructorHelpers::FObjectFinder<UInputAction> AttackActionRef(TEXT("/Game/Character/Input/Action/IA_Attack.IA_Attack"));
	if (AttackActionRef.Succeeded())
	{
		AttackAction = AttackActionRef.Object;
	}
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

void AP4PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (AP4CharacterPlayer* CharacterPlayer = Cast<AP4CharacterPlayer>(InPawn))
	{
		if (UAbilitySystemComponent* ASC = CharacterPlayer->GetAbilitySystemComponent())
		{
			// 캐릭터의 AbilityMap 읽기
			//for (const auto& Pair : Player->StartInputAbilities)
			//{
			//	const int32 InputID = Pair.Key;
			//	const TSubclassOf<UGameplayAbility> AbilityClass = Pair.Value;

			//	if (AbilityClass)
			//	{
			//		FGameplayAbilitySpec Spec(AbilityClass, 1, InputID, this);
			//		ASC->GiveAbility(Spec);
			//	}
			//}

			// 블루프린트에서 설정해준 초기 어빌리티 부여(인풋X)
			for (const auto& StartAbility : CharacterPlayer->StartAbilities)
			{
				FGameplayAbilitySpec StartSpec(StartAbility);
				ASC->GiveAbility(StartSpec);
			}

			// 블루프린트에서 설정해준 초기 어빌리티 부여(인풋O)
			for (const auto& StartInputAbility : CharacterPlayer->StartInputAbilities)
			{
				FGameplayAbilitySpec StartSpec(StartInputAbility.Value);
				StartSpec.InputID = StartInputAbility.Key;
				ASC->GiveAbility(StartSpec);
			}

			SetupGASInputBindings(ASC);
		}
	}
}

void AP4PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AP4PlayerController::HandleMove);
		EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &AP4PlayerController::HandleLook);
		//EIC->BindAction(JumpAction, ETriggerEvent::Started, this, &AP4PlayerController::HandleJumpStart);
		//EIC->BindAction(JumpAction, ETriggerEvent::Completed, this, &AP4PlayerController::HandleJumpEnd);

		//EIC->BindAction(AttackAction, ETriggerEvent::Started, this, &AP4PlayerController::HandleAttack);
		//SetupPlayerGAS();
	}
}

void AP4PlayerController::SetupGASInputBindings(UAbilitySystemComponent* ASC)
{
	if (!ASC || !InputComponent) return;

	if (auto* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Ability Input (InputID Jump = 0, Attack = 1)
		EIC->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AP4PlayerController::HandleAbilityPressed, 0);
		EIC->BindAction(JumpAction, ETriggerEvent::Completed, this, &AP4PlayerController::HandleAbilityReleased, 0);
		EIC->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AP4PlayerController::HandleAbilityPressed, 1);
		//EIC->BindAction(RollAction, ETriggerEvent::Triggered, this, &AP4PlayerController::HandleAbilityPressed, 2);
		//EIC->BindAction(RollAction, ETriggerEvent::Completed, this, &AP4PlayerController::HandleAbilityReleased, 2);
	}
}

void AP4PlayerController::HandleAbilityPressed(int32 InputID)
{
	if (AP4CharacterPlayer* CharacterPlayer = Cast<AP4CharacterPlayer>(GetPawn()))
	{
		CharacterPlayer->GASInputPressed(InputID);
	}
		
}

void AP4PlayerController::HandleAbilityReleased(int32 InputID)
{
	if (AP4CharacterPlayer* CharacterPlayer = Cast<AP4CharacterPlayer>(GetPawn()))
	{
		CharacterPlayer->GASInputReleased(InputID);
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