// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/P4Slot.h"
#include "Item/ItemDataBase.h"

void UP4Slot::Init()
{
	// 장비 타입 아이템 델리게이트 Map에 저장
	FGameplayTag EquipmentTag = FGameplayTag::RequestGameplayTag(FName("Item.Equipment"));
	SlotUpdateActions.Add(
		EquipmentTag,
		FUpdateSlotDelegateWrapper(
			FOnUpdateSlotDelegate::CreateUObject(
				this,
				&UP4Slot::UpdateEquipmentSlot
			)
		)
	);

	// 소비 타입 아이템 델리게이트 Map에 저장
	FGameplayTag ConsumableTag = FGameplayTag::RequestGameplayTag(FName("Item.Consumable"));
	SlotUpdateActions.Add(
		ConsumableTag,
		FUpdateSlotDelegateWrapper(
			FOnUpdateSlotDelegate::CreateUObject(
				this,
				&UP4Slot::UpdateConsumableSlot
			)
		)
	);
}

void UP4Slot::UpdateSlot()
{
	FGameplayTag ItemTags;
	// 슬롯 타입에 따라 실행되는 함수 호출
	SlotUpdateActions[ItemTags].SlotDelegate.ExecuteIfBound();
}

void UP4Slot::NativeConstruct()
{
	Super::NativeConstruct();
}

void UP4Slot::UpdateEquipmentSlot()
{
}

void UP4Slot::UpdateConsumableSlot()
{
}
