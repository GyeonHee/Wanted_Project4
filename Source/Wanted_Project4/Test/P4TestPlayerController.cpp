// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/P4TestPlayerController.h"
#include "UI/P4CustomWidget.h"
#include "Test/P4TestCharacter.h"
#include "UI/P4InventoryWidget.h"
#include "Inventory/P4InventoryComponent.h"

AP4TestPlayerController::AP4TestPlayerController()
{
	bShowMouseCursor = false;  // 게임 시작 시 커서 숨김
}

void AP4TestPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay"));

	// 입력 모드 초기화
	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}

void AP4TestPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UE_LOG(LogTemp, Warning, TEXT("=== SetupInputComponent 호출됨 ==="));

	// 입력 바인딩
	InputComponent->BindAction("ToggleInventory", IE_Pressed, this, &AP4TestPlayerController::ToggleInventory);
}

void AP4TestPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

    UE_LOG(LogTemp, Warning, TEXT("=== OnPossess 호출됨 ==="));

    // 🔥 디버깅: 현재 실행 중인 Controller 클래스 확인
    UE_LOG(LogTemp, Warning, TEXT("현재 Controller 클래스: %s"), *GetClass()->GetName());
    UE_LOG(LogTemp, Warning, TEXT("Is Blueprint: %s"), GetClass()->IsChildOf(UBlueprintGeneratedClass::StaticClass()) ?
        TEXT("YES") : TEXT("NO"));

    // 🔥 디버깅: InventoryWidgetClass 상태
    if (InventoryWidgetClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("InventoryWidgetClass 설정됨: %s"),
            *InventoryWidgetClass->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("InventoryWidgetClass가 nullptr!"));
        UE_LOG(LogTemp, Error, TEXT("현재 사용 중인 Controller: %s"), *GetClass()->GetName());
        UE_LOG(LogTemp, Error, TEXT("BP_TestPlayerController를 사용하고 있는지 확인 필요!"));
    }

    // 캐릭터 캐스팅
    AP4TestCharacter* TestChar = Cast<AP4TestCharacter>(InPawn);
    if (!TestChar)
    {
        UE_LOG(LogTemp, Error, TEXT("AP4TestCharacter로 캐스트 실패!"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("TestCharacter 캐스트 성공: %s"), *TestChar->GetName());

    // 인벤토리 컴포넌트 체크
    if (!TestChar->InventoryComp)
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
    InventoryWidget->BindInventory(TestChar->InventoryComp);
    UE_LOG(LogTemp, Warning, TEXT("인벤토리 위젯 바인딩 완료\n"));
}

void AP4TestPlayerController::ToggleInventory()
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
		InputMode.SetWidgetToFocus(InventoryWidget->TakeWidget());
		InputMode.SetHideCursorDuringCapture(false);
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(InputMode);

		UE_LOG(LogTemp, Warning, TEXT("인벤토리 열림"));
	}
	else
	{
		// 인벤토리 닫기
		InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		bShowMouseCursor = false;

		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);

		UE_LOG(LogTemp, Warning, TEXT("인벤토리 닫힘"));
	}
}
