// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/P4InventoryComponent.h"

// Sets default values for this component's properties
UP4InventoryComponent::UP4InventoryComponent()
{
	
}

bool UP4InventoryComponent::AddItem(UItemDataBase* ItemData, int32 Quantity)
{
    if (!ItemData) return false;

    // 1. 이미 같은 아이템이 있는지 찾기
    for (FInventoryItem& Item : InventoryItems)
    {
        if (Item.ItemData == ItemData)
        {
            // 같은 아이템 발견! 수량만 증가
            Item.Quantity += Quantity;
            OnInventoryUpdated.Broadcast();  // UI에게 알림!
            return true;
        }
    }

    // 2. 새로운 아이템이면 배열에 추가
    FInventoryItem NewItem;
    NewItem.ItemData = ItemData;
    NewItem.Quantity = Quantity;
    InventoryItems.Add(NewItem);

    OnInventoryUpdated.Broadcast();  // UI에게 알림!
    return true;
}

bool UP4InventoryComponent::RemoveItem(UItemDataBase* ItemData, int32 Quantity)
{
    if (!ItemData) return false;

    for (int32 i = 0; i < InventoryItems.Num(); ++i)
    {
        if (InventoryItems[i].ItemData == ItemData)
        {
            InventoryItems[i].Quantity -= Quantity;

            // 수량이 0 이하면 배열에서 제거
            if (InventoryItems[i].Quantity <= 0)
            {
                InventoryItems.RemoveAt(i);
            }

            OnInventoryUpdated.Broadcast();  // UI에게 알림!
            return true;
        }
    }

    return false;
}




