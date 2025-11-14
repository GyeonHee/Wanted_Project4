// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/P4PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "Character/P4CharacterPlayer.h"
#include "AbilitySystemComponent.h"
#include "UI/P4HUDWidget.h"
#include "UI/P4HpBarWidget.h"
#include "Attribute/P4PlayerAttributeSet.h"
#include "Inventory/P4InventoryComponent.h"
#include "UI/P4InventoryWidget.h"
#include "Character/Animation/P4PlayerAnimInstance.h"

AP4PlayerController::AP4PlayerController()
{
	// 게임 시작 시 커서 숨김
	// -작성: 노현기 -일시: 2025.11.10
	bShowMouseCursor = false;


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

	//작성- 한승헌 일시- 2025.11.12
	//InteractionAction 지정
	static ConstructorHelpers::FObjectFinder<UInputAction> InteractionActionRef(TEXT("/Game/Character/Input/Action/IA_Interaction.IA_Interaction"));
	if (InteractionActionRef.Succeeded())
	{
		InteractionAction = InteractionActionRef.Object;
	}

	//작성- 노현기 일시- 2025.11.14
	static ConstructorHelpers::FObjectFinder<UInputAction> InventoryActionRef(TEXT("/Game/Character/Input/Action/IA_Inventory.IA_Inventory"));
	if (InventoryActionRef.Succeeded())
	{
		InventoryAction = InventoryActionRef.Object;
	}

	//작성- 노현기 일시- 2025.11.14
	static ConstructorHelpers::FObjectFinder<UInputAction> DrawKatanaActionRef(TEXT("/Game/Character/Input/Action/IA_DrawKatana.IA_DrawKatana"));
	if (DrawKatanaActionRef.Succeeded())
	{
		DrawKatanaAction = DrawKatanaActionRef.Object;
	}

	//HUD 생성 -작성: 한승헌 -일시: 2025.11.07
	static ConstructorHelpers::FClassFinder<UP4HUDWidget> P4HUDWidgetRef(TEXT("/Game/UI/WBP_HUD.WBP_HUD_C"));

	if (P4HUDWidgetRef.Succeeded() == true)
	{
		P4HUDWidgetClass = P4HUDWidgetRef.Class;
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


	//HUD 생성 -작성: 한승헌 -일시: 2025.11.07
	P4HUDWidget = CreateWidget<UP4HUDWidget>(this, P4HUDWidgetClass);

	if (P4HUDWidget != nullptr)
	{
		P4HUDWidget->AddToViewport();

		if (AP4CharacterPlayer* CharacterPlayer = Cast<AP4CharacterPlayer>(GetPawn()))
		{
			if (UAbilitySystemComponent* ASC = CharacterPlayer->GetAbilitySystemComponent())
			{
				if (UP4HpBarWidget* HpBar = P4HUDWidget->GetHpBar())
				{
					HpBar->SetAbilitySystemComponent(CharacterPlayer);
				}
			}
		}
	}
	
}
//

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

			if (P4HUDWidget != nullptr && P4HUDWidget->GetHpBar() != nullptr)
			{
				P4HUDWidget->GetHpBar()->SetAbilitySystemComponent(CharacterPlayer);
			}
		}
	}

	// -작성: 노현기 -일시: 2025.11.10
	if (AP4CharacterPlayer* CharacterPlayer = Cast<AP4CharacterPlayer>(InPawn))
	{
		// 인벤토리 컴포넌트 체크
		if (!CharacterPlayer->GetInventoryComponent())
		{
			UE_LOG(LogTemp, Error, TEXT("InventoryComp가 nullptr!"));
			return;
		}

		UE_LOG(LogTemp, Warning, TEXT("InventoryComp 존재 확인"));

		// 위젯이 아직 생성되지 않았으면 생성
		if (!InventoryWidget)
		{
			if (!InventoryWidgetClass)
			{
				UE_LOG(LogTemp, Error, TEXT("InventoryWidgetClass가 설정되지 않음!"));
				return;
			}

			UE_LOG(LogTemp, Warning, TEXT("인벤토리 위젯 생성 시작..."));

			InventoryWidget = CreateWidget<UP4InventoryWidget>(this, InventoryWidgetClass);
			if (!InventoryWidget)
			{
				UE_LOG(LogTemp, Error, TEXT("인벤토리 위젯 생성 실패!"));
				return;
			}

			InventoryWidget->AddToViewport();
			InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
			UE_LOG(LogTemp, Warning, TEXT("인벤토리 위젯 생성 완료"));
		}

		// 인벤토리 바인딩
		InventoryWidget->BindInventory(CharacterPlayer->GetInventoryComponent());
		UE_LOG(LogTemp, Warning, TEXT("인벤토리 위젯 바인딩 완료\n"));
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

		// -작성: 노현기 -일시: 2025.11.14
		EIC->BindAction(InventoryAction, ETriggerEvent::Started, this, &AP4PlayerController::ToggleInventory);
		EIC->BindAction(DrawKatanaAction, ETriggerEvent::Started, this, &AP4PlayerController::ToggleHandOnWeapon);
	}

	//// 입력 바인딩 ('I' 키눌러서 인벤토리 토글) 
	//// @Todo: 이거 프로젝트 세팅에서 입력 바인딩에서 키 설정해야하는거로 알고있어요 메인 레벨에서 해야함(되어있음)
	//// -작성: 노현기 -일시: 2025.11.10
	//InputComponent->BindAction("ToggleInventory", IE_Pressed, this, &AP4PlayerController::ToggleInventory);
	////-작성: 노현기 - 일시 : 2025.11.14
	//InputComponent->BindAction("ToggleHandOnWeapon", IE_Pressed, this, &AP4PlayerController::ToggleHandOnWeapon);
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

		//작성: 한승헌
		//일시: 2025.11.12
		//NPC와 상호작용을 위한 입력 키.
		EIC->BindAction(InteractionAction, ETriggerEvent::Triggered, this, &AP4PlayerController::HandleAbilityPressed, 2);
	}
}

void AP4PlayerController::HandleAbilityPressed(int32 InputID)
{
	// -작성자: 노현기 -일시: 2025.11.12
    // 공격 입력(1번)이고, 인벤토리가 열려있으면
	if (InputID == 1 && bIsInventoryVisible && InventoryWidget)
	{
		// 인벤토리 위젯에게 마우스가 위에 있는지 물어봄
		if (InventoryWidget->IsMouseOverInventory())
		{
			UE_LOG(LogTemp, Warning, TEXT("인벤토리 위에서 클릭 - 공격 차단"));
			return; // 공격 차단
		}
	}
	

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


//작성 - 한승헌 2025-11-10
//임시
void AP4PlayerController::DebugDamage(float Amount)
{
	if (auto* CP = Cast<AP4CharacterPlayer>(GetPawn()))
		if (auto* ASC = CP->GetAbilitySystemComponent())
		{
			// Health에서 Amount만큼 감소
			ASC->ApplyModToAttribute(UP4PlayerAttributeSet::GetHealthAttribute(),
				EGameplayModOp::Additive, -FMath::Abs(Amount));
			UE_LOG(LogTemp, Log, TEXT("[DebugDamage] HP -%0.1f"), Amount);
		}
}

// -작성: 노현기 -일시: 2025.11.10
void AP4PlayerController::ToggleInventory()
{
	UE_LOG(LogTemp, Warning, TEXT("ToggleInventory 입력 감지"));

	if (!InventoryWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("InventoryWidget이 nullptr!"));
		return;
	}

	// 상태 토글
	bIsInventoryVisible = !bIsInventoryVisible;

	if (bIsInventoryVisible)
	{
		// 인벤토리 열기
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);
		bShowMouseCursor = true;

		FInputModeGameAndUI InputMode;
		// SetWidgetToFocus()는 키보드 입력이 필요한 UI(텍스트 입력 등)에서만 필요합니다
		//InputMode.SetWidgetToFocus(InventoryWidget->TakeWidget());
		InputMode.SetHideCursorDuringCapture(false);
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(InputMode);

		// 마우스 이벤트가 UI를 먼저 거치도록 설정
		bShowMouseCursor = true;
		//FlushPressedKeys(); // 이전 입력 초기화

		UE_LOG(LogTemp, Warning, TEXT("인벤토리 열림"));
	}
	else
	{
		// 인벤토리 닫기
		InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		bShowMouseCursor = false;

		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);

		FlushPressedKeys(); // 입력 초기화

		UE_LOG(LogTemp, Warning, TEXT("인벤토리 닫힘"));
	}
}

// -작성: 노현기 -일시: 2025.11.14
void AP4PlayerController::ToggleHandOnWeapon()
{
	UE_LOG(LogTemp, Warning, TEXT("ToggleHandOnWeapon 입력 감지"));

	AP4CharacterPlayer* P4Character = Cast<AP4CharacterPlayer>(GetPawn());
	if (!P4Character)
	{
		UE_LOG(LogTemp, Error, TEXT("P4Character를 찾을 수 없습니다!"));
		return;
	}

	USkeletalMeshComponent* MeshComp = P4Character->GetMesh();
	UP4PlayerAnimInstance* AnimInst = MeshComp ? Cast<UP4PlayerAnimInstance>(MeshComp->GetAnimInstance()) : nullptr;

	if (!AnimInst)
	{
		UE_LOG(LogTemp, Error, TEXT("AnimInstance를 찾을 수 없습니다!"));
		return;
	}

	// ⭐ bIsEquipped 상태 로그 출력
	UE_LOG(LogTemp, Warning, TEXT("현재 bIsEquipped: %s"), AnimInst->bIsEquipped ? TEXT("true") : TEXT("false"));

	// ⭐ 먼저 장착되어 있는지 확인
	if (!AnimInst->bIsEquipped)
	{
		UE_LOG(LogTemp, Warning, TEXT("무기가 장착되지 않았습니다! 발도/납도 불가능"));
		return;
	}

	// ⭐ 상태 토글 (손에 쥐고 있는지)
	bIsEquip = !bIsEquip;

	UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();
	if (!AnimInstance) return;

	if (bIsEquip)
	{
		// 발도 (등 → 손)
		UAnimMontage* DrawMontage = P4Character->GetDrawKatanaMontage();

		UE_LOG(LogTemp, Warning, TEXT("DrawMontage 포인터: %s"), DrawMontage ? TEXT("Valid") : TEXT("nullptr"));

		if (DrawMontage)
		{
			float PlayLength = AnimInstance->Montage_Play(DrawMontage);
			UE_LOG(LogTemp, Warning, TEXT("DrawKatana 몽타주 재생! 길이: %f"), PlayLength);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("DrawKatana 몽타주가 설정되지 않았습니다!"));
		}

		// ⭐ 임시로 여기서도 설정
		AnimInst->bIsKatanaOnHand = true;
		UE_LOG(LogTemp, Warning, TEXT("bIsKatanaOnHand = true"));
	}
	else
	{
		// 납도 (손 → 등)
		UAnimMontage* SheathMontage = P4Character->GetSheathKatanaMontage();

		UE_LOG(LogTemp, Warning, TEXT("SheathMontage 포인터: %s"), SheathMontage ? TEXT("Valid") : TEXT("nullptr"));

		if (SheathMontage)
		{
			float PlayLength = AnimInstance->Montage_Play(SheathMontage);
			UE_LOG(LogTemp, Warning, TEXT("SheathKatana 몽타주 재생! 길이: %f"), PlayLength);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("SheathKatana 몽타주가 설정되지 않았습니다!"));
		}

		// ⭐ 임시로 여기서도 설정
		AnimInst->bIsKatanaOnHand = false;
		UE_LOG(LogTemp, Warning, TEXT("bIsKatanaOnHand = false"));
	}
}
