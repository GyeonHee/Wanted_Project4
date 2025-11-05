// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/P4TestPlayerController.h"
#include "UI/P4CustomWidget.h"

AP4TestPlayerController::AP4TestPlayerController()
{
	bShowMouseCursor = true;

	static ConstructorHelpers::FClassFinder<UP4CustomWidget> P4CustomWidgetRef(
		TEXT("/Game/UI/WBP_Inventory.WBP_Inventory_C")
	);
	if (P4CustomWidgetRef.Succeeded())
	{
		InventoryWidgetClass = P4CustomWidgetRef.Class;
	}
}

void AP4TestPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);

	// CreateWidget
	InventoryWidget = CreateWidget<UP4CustomWidget>(this, InventoryWidgetClass);
	// 문제 없이 생성됐으면, 뷰포트에 추가
	if (InventoryWidget)
	{
		InventoryWidget->AddToViewport();
		InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AP4TestPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("ToggleInventory", IE_Pressed, this, &AP4TestPlayerController::ToggleInventory);
}

void AP4TestPlayerController::ToggleInventory()
{
	if (!InventoryWidget) return;

	bIsInventoryVisible = !bIsInventoryVisible;
	InventoryWidget->SetVisibility(bIsInventoryVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);

	if (bIsInventoryVisible)
	{
		bShowMouseCursor = true;

		// UI와 게임 둘 다 입력 받을 수 있게 변경
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(InventoryWidget->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(InputMode);
	}
	else
	{
		bShowMouseCursor = false;

		// 게임 모드로 다시 전환
		SetInputMode(FInputModeGameOnly());
	}
}
