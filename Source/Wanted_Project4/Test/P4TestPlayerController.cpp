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

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);

	UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay"));
}

void AP4TestPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UE_LOG(LogTemp, Warning, TEXT("=== SetupInputComponent 호출됨 ==="));

	// 입력 바인딩
	InputComponent->BindAction("ToggleInventory", IE_Pressed, this, &AP4TestPlayerController::ToggleInventory);
}

void AP4TestPlayerController::ConnectInventoryWidget()
{
	UE_LOG(LogTemp, Warning, TEXT("=== ConnectInventoryWidget 호출됨 ==="));

	if (!InventoryWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("InventoryWidget이 nullptr!"));
		return;
	}

	ACharacter* MyChar = GetCharacter();
	if (!MyChar)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetCharacter() 실패 - 아직 캐릭터 빙의 안 됨"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("캐릭터 찾음: %s"), *MyChar->GetName());

	AP4TestCharacter* TestChar = Cast<AP4TestCharacter>(MyChar);
	if (!TestChar)
	{
		UE_LOG(LogTemp, Error, TEXT("AP4TestCharacter로 캐스트 실패!"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("TestCharacter 캐스트 성공"));

	if (!TestChar->InventoryComp)
	{
		UE_LOG(LogTemp, Error, TEXT("InventoryComp가 nullptr!"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("InventoryComp 존재 확인"));
	UE_LOG(LogTemp, Warning, TEXT("현재 인벤토리 아이템 개수: %d"),
		TestChar->InventoryComp->GetInventoryItems().Num());

	UP4InventoryWidget* InvWidget = Cast<UP4InventoryWidget>(InventoryWidget);
	if (!InvWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("UP4InventoryWidget으로 캐스트 실패!"));
		UE_LOG(LogTemp, Error, TEXT("   실제 클래스: %s"), *InventoryWidget->GetClass()->GetName());
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("InventoryWidget 캐스트 성공"));

	//  이미 연결되어 있으면 다시 안 함
	if (InvWidget->InventoryComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("⚠️ 이미 인벤토리가 연결되어 있음 - 스킵"));
		return;
	}

	InvWidget->BindInventory(TestChar->InventoryComp);
	UE_LOG(LogTemp, Warning, TEXT("=== 인벤토리 위젯 연결 완료 ===\n"));
}

void AP4TestPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UE_LOG(LogTemp, Warning, TEXT("=== OnPossess 호출됨 ==="));

	if (!InventoryWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("InventoryWidget이 nullptr!"));
		return;
	}

	AP4TestCharacter* TestChar = Cast<AP4TestCharacter>(InPawn);
	if (!TestChar)
	{
		UE_LOG(LogTemp, Error, TEXT("AP4TestCharacter로 캐스트 실패!"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("TestCharacter 캐스트 성공: %s"), *TestChar->GetName());

	if (!TestChar->InventoryComp)
	{
		UE_LOG(LogTemp, Error, TEXT("InventoryComp가 nullptr!"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("InventoryComp 존재 확인"));
	UE_LOG(LogTemp, Warning, TEXT("현재 인벤토리 아이템 개수: %d"),
		TestChar->InventoryComp->GetInventoryItems().Num());

	UP4InventoryWidget* InvWidget = Cast<UP4InventoryWidget>(InventoryWidget);
	if (!InvWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("UP4InventoryWidget으로 캐스트 실패!"));
		UE_LOG(LogTemp, Error, TEXT("   실제 클래스: %s"), *InventoryWidget->GetClass()->GetName());
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("InventoryWidget 캐스트 성공"));

	InvWidget->BindInventory(TestChar->InventoryComp);
	UE_LOG(LogTemp, Warning, TEXT("=== 인벤토리 위젯 연결 완료 ===\n"));
}

void AP4TestPlayerController::ToggleInventory()
{
	UE_LOG(LogTemp, Warning, TEXT("ToggleInventory 입력 감지"));

	// 캐릭터에게 토글 요청
	AP4TestCharacter* TestChar = Cast<AP4TestCharacter>(GetCharacter());
	if (TestChar)
	{
		TestChar->ToggleInventory();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("❌ 캐릭터를 찾을 수 없음!"));
	}
}
