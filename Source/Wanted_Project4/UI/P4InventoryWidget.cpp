// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/P4InventoryWidget.h"
#include "Item/ItemDataBase.h"
#include "Inventory/P4Slot.h"
#include "Components/UniformGridPanel.h"
#include "Components/Widget.h"
#include "Inventory/P4InventoryTags.h"
#include "Components/CanvasPanel.h"
#include "BluePrint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "BluePrint/WidgetLayoutLibrary.h"
#include "Player/P4PlayerController.h"

UP4InventoryWidget::UP4InventoryWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UP4InventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	EquipmentSlots.Empty();
	ConsumableSlots.Empty();

	if (EquipmentTypeSlot)
	{
		for (UWidget* Child : EquipmentTypeSlot->GetAllChildren())
		{
			if (UP4Slot* SlotWidget = Cast<UP4Slot>(Child))
			{
                SlotWidget->SlotType = EInventorySlotType::Equipment;
				EquipmentSlots.Add(SlotWidget);

				UE_LOG(LogTemp, Warning, TEXT("장비 슬롯 추가됨: %s, 인덱스: %d"), *SlotWidget->GetName(), SlotWidget->SlotIndex);
			}
		}
	}

	if (ConsumableTypeSlot)
	{
		for (UWidget* Child : ConsumableTypeSlot->GetAllChildren())
		{
			if (UP4Slot* SlotWidget = Cast<UP4Slot>(Child))
			{
                SlotWidget->SlotType = EInventorySlotType::Consumable;
				ConsumableSlots.Add(SlotWidget);
				UE_LOG(LogTemp, Warning, TEXT("소비 슬롯 추가됨: %s, 인덱스: %d"), *SlotWidget->GetName(), SlotWidget->SlotIndex);
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("장비 슬롯 개수: %d, 소비 슬롯 개수: %d"), EquipmentSlots.Num(), ConsumableSlots.Num());


    bIsDragging = false;

    // InventoryPanel 찾기 및 디버깅 (BindWidget 사용 시)
    if (InventoryPanel)
    {
        FVector2D PanelSize = InventoryPanel->GetCachedGeometry().GetLocalSize();
        UE_LOG(LogTemp, Warning, TEXT("InventoryPanel 크기: %s"), *PanelSize.ToString());
    }
    else
    {
        // BindWidget이 안 되었으면 수동으로 찾기
        UE_LOG(LogTemp, Warning, TEXT("InventoryPanel이 바인딩되지 않음, 수동 검색 중..."));

        TArray<UWidget*> AllWidgets;
        WidgetTree->GetAllWidgets(AllWidgets);

        for (UWidget* Widget : AllWidgets)
        {
            if (UCanvasPanel* Panel = Cast<UCanvasPanel>(Widget))
            {
                // 루트가 아닌 Canvas Panel 찾기
                if (Panel != GetRootWidget())
                {
                    InventoryPanel = Panel;
                    UE_LOG(LogTemp, Warning, TEXT("InventoryPanel 수동 검색 성공: %s"), *Panel->GetName());
                    break;
                }
            }
        }
    }

}

void UP4InventoryWidget::BindInventory(UP4InventoryComponent* InInventoryComp)
{
    UE_LOG(LogTemp, Warning, TEXT("=== BindInventory 호출됨 ==="));

    if (!InInventoryComp)
    {
        UE_LOG(LogTemp, Error, TEXT("InInventoryComp가 nullptr입니다!"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("InventoryComp 바인딩 성공"));

    // 1. 인벤토리 컴포넌트 저장
    InventoryComp = InInventoryComp;

    // 2. 델리게이트 바인딩 (인벤토리가 변경되면 RefreshUI 자동 호출)
    InventoryComp->OnInventoryUpdated.AddUObject(this, &UP4InventoryWidget::RefreshSlot);
    UE_LOG(LogTemp, Warning, TEXT("델리게이트 바인딩 완료"));

    // 3. 처음 한 번 UI 업데이트
    UE_LOG(LogTemp, Warning, TEXT("첫 RefreshUI 호출 시작"));
    RefreshUI();
}

void UP4InventoryWidget::RefreshUI()
{
    UE_LOG(LogTemp, Warning, TEXT("=== RefreshUI 호출됨 ==="));

    if (!InventoryComp)
    {
        UE_LOG(LogTemp, Error, TEXT("InventoryComp가 nullptr입니다!"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("InventoryComp 존재함"));

    // 장비 인벤토리 갱신
    const TArray<FInventoryItem>* EquipItems = InventoryComp->GetInventoryByType(EInventorySlotType::Equipment);
    if (EquipItems)
    {
        for (int32 i = 0; i < EquipmentSlots.Num() && i < EquipItems->Num(); ++i)
        {
            EquipmentSlots[i]->SetItem((*EquipItems)[i]);
        }
    }

    // 소비 인벤토리 갱신
    const TArray<FInventoryItem>* ConsumItems = InventoryComp->GetInventoryByType(EInventorySlotType::Consumable);
    if (ConsumItems)
    {
        for (int32 i = 0; i < ConsumableSlots.Num() && i < ConsumItems->Num(); ++i)
        {
            ConsumableSlots[i]->SetItem((*ConsumItems)[i]);
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("=== RefreshUI 완료 ===\n"));
}

void UP4InventoryWidget::RefreshSlot(EInventorySlotType SlotType, int32 SlotIndex)
{
    if (!InventoryComp)
    {
        UE_LOG(LogTemp, Error, TEXT("RefreshSlot: InventoryComp가 nullptr"));
        return;
    }

    // 해당 타입의 인벤토리 배열 가져오기
    const TArray<FInventoryItem>* TargetArray = InventoryComp->GetInventoryByType(SlotType);
    if (!TargetArray || !TargetArray->IsValidIndex(SlotIndex))
    {
        UE_LOG(LogTemp, Error, TEXT("RefreshSlot: 잘못된 타입[%d] 또는 인덱스[%d]"), (int32)SlotType, SlotIndex);
        return;
    }

    // 해당 타입의 UI 슬롯 배열 가져오기
    TArray<TObjectPtr<UP4Slot>>* SlotArray = nullptr;

    switch (SlotType)
    {
    case EInventorySlotType::Equipment:
        SlotArray = &EquipmentSlots;
        break;
    case EInventorySlotType::Consumable:
        SlotArray = &ConsumableSlots;
        break;
        //  나중에 타입 추가 시
        // case EInventorySlotType::Material:
        //     SlotArray = &MaterialSlots;
        //     break;
    default:
        UE_LOG(LogTemp, Error, TEXT("RefreshSlot: 알 수 없는 SlotType[%d]"), (int32)SlotType);
        return;
    }

    // UI 슬롯 배열 유효성 검사
    if (!SlotArray || !SlotArray->IsValidIndex(SlotIndex))
    {
        UE_LOG(LogTemp, Error, TEXT("RefreshSlot: UI 슬롯 배열 인덱스[%d] 유효하지 않음"), SlotIndex);
        return;
    }

    // 해당 슬롯만 갱신
    (*SlotArray)[SlotIndex]->SetItem((*TargetArray)[SlotIndex]);

    UE_LOG(LogTemp, Log, TEXT("RefreshSlot: 타입[%d] 인덱스[%d] 갱신 완료"), (int32)SlotType, SlotIndex);
}

FReply UP4InventoryWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    // InventoryPanel 영역 내부 클릭인지 체크
    if (InventoryPanel)
    {
        FGeometry PanelGeometry = InventoryPanel->GetCachedGeometry();
        FVector2D LocalMousePos = PanelGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
        FVector2D PanelSize = PanelGeometry.GetLocalSize();

        // InventoryPanel 영역 내부인지 확인
        if (LocalMousePos.X >= 0 && LocalMousePos.X <= PanelSize.X &&
            LocalMousePos.Y >= 0 && LocalMousePos.Y <= PanelSize.Y)
        {
            UE_LOG(LogTemp, Warning, TEXT("인벤토리 내부 클릭 - 게임 입력 차단"));

            Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
            return FReply::Handled();
        }
    }

    // 인벤토리 외부 클릭 - 게임 입력 허용
    UE_LOG(LogTemp, Log, TEXT("인벤토리 외부 클릭 - 게임 입력 허용"));
    return FReply::Unhandled();
   
}

bool UP4InventoryWidget::IsMouseOverInventory() const
{
    // 위젯이 보이지 않으면 false
    if (GetVisibility() != ESlateVisibility::Visible)
    {
        return false;
    }

    // InventoryPanel이 있으면 그것을 체크, 없으면 전체 위젯 체크
    if (InventoryPanel)
    {
        bool bIsHovered = InventoryPanel->IsHovered();
        UE_LOG(LogTemp, Log, TEXT("InventoryPanel IsHovered: %s"), bIsHovered ? TEXT("true") : TEXT("false"));
        return bIsHovered;
    }

    bool bIsHovered = this->IsHovered();
    UE_LOG(LogTemp, Log, TEXT("InventoryWidget IsHovered: %s"), bIsHovered ? TEXT("true") : TEXT("false"));
    return bIsHovered;
}


//void UP4InventoryWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
//{
//    Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
//}
//
//bool UP4InventoryWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
//{
//    Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
//
//    MoveEnd();
//    return true;
//}
//
//void UP4InventoryWidget::NativeTick(const FGeometry& InGeometry, float InDeltaTime)
//{
//    Super::NativeTick(InGeometry, InDeltaTime);
//
//    // 드래그 중이라면
//    if (bIsDragging)
//    {
//        FVector2D MousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
//
//        // 초기 마우스 위치와의 차이 계산
//        float DeltaX = InitialOffset.X - MousePos.X;
//        float DeltaY = InitialOffset.Y - MousePos.Y;
//
//        // 초기 마우스 위치와의 차이를 초기 위젯 위치에 반영
//        InitialPos.X += -DeltaX;
//        InitialPos.Y += -DeltaY;
//
//        // 오프셋 재설정 (이전 마우스 위치 -> 현재 마우스 위치)
//        InitialOffset = MousePos;
//
//        // 오버레이 위치 재설정
//        UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(Overlay);
//        if (CanvasPanelSlot)
//        {
//            CanvasPanelSlot->SetPosition(InitialPos);
//        }
//    }
//}
//
//void UP4InventoryWidget::MoveStart()
//{
//    bIsDragging = true;
//    UE_LOG(LogTemp, Log, TEXT("MoveStart() bIsDragging = true"));
//
//    // 오버레이 현재 위치 구해 저장
//    FVector2D WidgetPos;
//    UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(Overlay);
//    
//    if (CanvasPanelSlot)
//    {
//        WidgetPos = CanvasPanelSlot->GetPosition();
//    }
//    InitialPos = WidgetPos;
//
//    // 마우스 현재 위치 구해 저장
//    InitialOffset = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
//}
//
//void UP4InventoryWidget::MoveEnd()
//{
//    bIsDragging = false;
//
//    UE_LOG(LogTemp, Log, TEXT("MoveEnd() bIsDragging = false"));
//}
