// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/P4InventoryWidget.h"
#include "Item/ItemDataBase.h"
#include "Inventory/P4Slot.h"
#include "Components/UniformGridPanel.h"
#include "Inventory/P4InventoryComponent.h"
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
				EquipmentSlots.Add(SlotWidget);
				UE_LOG(LogTemp, Warning, TEXT("장비 슬롯 추가됨: %s"), *SlotWidget->GetName());
			}
		}
	}

	if (ConsumableTypeSlot)
	{
		for (UWidget* Child : ConsumableTypeSlot->GetAllChildren())
		{
			if (UP4Slot* SlotWidget = Cast<UP4Slot>(Child))
			{
				ConsumableSlots.Add(SlotWidget);
				UE_LOG(LogTemp, Warning, TEXT("소비 슬롯 추가됨: %s"), *SlotWidget->GetName());
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
    InventoryComp->OnInventoryUpdated.AddUObject(this, &UP4InventoryWidget::RefreshUI);
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

    // 인벤토리 데이터 가져오기
    const TArray<FInventoryItem>& Items = InventoryComp->GetInventoryItems();
    UE_LOG(LogTemp, Warning, TEXT("인벤토리 아이템 개수: %d"), Items.Num());

    // 슬롯 개수 확인
    UE_LOG(LogTemp, Warning, TEXT("장비 슬롯 개수: %d, 소비템 슬롯 개수: %d"), EquipmentSlots.Num(),
        ConsumableSlots.Num());

    //// Equipment 태그를 정의 (프로젝트 설정에서 만든 태그 사용)
    //FGameplayTag EquipmentTag = FGameplayTag::RequestGameplayTag(FName("Item.Equipment"));
    //FGameplayTag ConsumableTag = FGameplayTag::RequestGameplayTag(FName("Item.Consumable"));

    //UE_LOG(LogTemp, Warning, TEXT("EquipmentTag Valid: %s"), EquipmentTag.IsValid() ? TEXT("Yes") :
    //    TEXT("No"));
    //UE_LOG(LogTemp, Warning, TEXT("ConsumableTag Valid: %s"), ConsumableTag.IsValid() ? TEXT("Yes") :
    //    TEXT("No"));

    // 장비 슬롯 인덱스, 소비템 슬롯 인덱스
    int32 EquipSlotIndex = 0;
    int32 ConsumSlotIndex = 0;

    // 모든 아이템을 순회하면서 슬롯에 배치
    for (const FInventoryItem& Item : Items)
    {
        if (!Item.ItemData)
        {
            UE_LOG(LogTemp, Warning, TEXT("ItemData가 nullptr인 아이템 발견"));
            continue;
        }

        UE_LOG(LogTemp, Warning, TEXT("아이템: %s, 수량: %d"), *Item.ItemData->GetItemName().ToString(),
            Item.Quantity);

        // 아이템의 태그 확인
        FGameplayTagContainer ItemTags = Item.ItemData->GetItemTags();
        UE_LOG(LogTemp, Warning, TEXT("   태그 개수: %d"), ItemTags.Num());

        for (const FGameplayTag& Tag : ItemTags)
        {
            UE_LOG(LogTemp, Warning, TEXT("   - 태그: %s"), *Tag.ToString());
        }

        // FItemData 구조체 생성 (슬롯이 이해하는 형식)
        FInventoryItem SlotData;
        SlotData.ItemData = Item.ItemData;
        SlotData.Quantity = Item.Quantity;

        // 아이템 타입에 따라 적절한 슬롯에 배치
        if (Item.ItemData->HasTag(P4InventoryTags::Item::Equipment))
        {
            UE_LOG(LogTemp, Warning, TEXT("장비 아이템으로 분류됨"));
            // 장비 슬롯에 추가
            if (EquipSlotIndex < EquipmentSlots.Num())
            {
                UE_LOG(LogTemp, Warning, TEXT("장비 슬롯[%d]에 추가"), EquipSlotIndex);
                //EquipmentSlots[EquipSlotIndex]->SetItem(SlotData);
                EquipSlotIndex++;
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("장비 슬롯이 꽉 참!"));
            }
        }
        else if (Item.ItemData->HasTag(P4InventoryTags::Item::Consumable))
        {
            UE_LOG(LogTemp, Warning, TEXT("소비템으로 분류됨"));
            // 소비템 슬롯에 추가
            if (ConsumSlotIndex < ConsumableSlots.Num())
            {
                UE_LOG(LogTemp, Warning, TEXT("소비템 슬롯[%d]에 추가"), ConsumSlotIndex);
                //ConsumableSlots[ConsumSlotIndex]->SetItem(SlotData);
                ConsumSlotIndex++;
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("소비템 슬롯이 꽉 참!"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("아이템 태그가 Equipment도 Consumable도 아님!"));
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("최종 배치 개수 - 장비: %d, 소비템: %d"), EquipSlotIndex, ConsumSlotIndex);

    // 남은 빈 슬롯들은 클리어
    for (int32 i = EquipSlotIndex; i < EquipmentSlots.Num(); ++i)
    {
        EquipmentSlots[i]->ClearSlot();
    }

    for (int32 i = ConsumSlotIndex; i < ConsumableSlots.Num(); ++i)
    {
        ConsumableSlots[i]->ClearSlot();
    }

    UE_LOG(LogTemp, Warning, TEXT("=== RefreshUI 완료 ===\n"));
}
