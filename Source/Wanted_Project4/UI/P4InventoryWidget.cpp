// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/P4InventoryWidget.h"
#include "Item/ItemDataBase.h"
#include "Inventory/P4Slot.h"
#include "Components/UniformGridPanel.h"
#include "Components/Widget.h"
#include "Inventory/P4InventoryTags.h"


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
