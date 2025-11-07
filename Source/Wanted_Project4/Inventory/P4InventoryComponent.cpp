// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/P4InventoryComponent.h"
#include "GameplayAbilities/Public/AbilitySystemInterface.h"
#include "GameplayAbilities/Public/AbilitySystemComponent.h"

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
            // 스택 최대치 확인
            int32 MaxStack = ItemData->GetMaxStackCount();
            int32 CanAdd = FMath::Min(Quantity, MaxStack - Item.Quantity);

            if (CanAdd > 0)
            {
                Item.Quantity += CanAdd;
                OnInventoryUpdated.Broadcast();

                // 남은 수량이 있으면 새 슬롯에 추가 시도
                if (Quantity - CanAdd > 0)
                {
                    return AddItem(ItemData, Quantity - CanAdd);
                }
                return true;
            }
        }
    }

    // 2. 새 슬롯 필요 - 용량 체크
    if (!HasSpace(ItemData))
    {
        UE_LOG(LogTemp, Warning, TEXT("인벤토리가 꽉 찼습니다!"));
        return false;
    }

    // 3. 새로운 아이템이면 배열에 추가
    FInventoryItem NewItem;
    NewItem.ItemData = ItemData;
    NewItem.Quantity = FMath::Min(Quantity, ItemData->GetMaxStackCount());;
    InventoryItems.Add(NewItem);

    OnInventoryUpdated.Broadcast();  // UI에게 알림!

    // 남은 수량이 있으면 재귀 호출
    if (Quantity > NewItem.Quantity)
    {
        return AddItem(ItemData, Quantity - NewItem.Quantity);
    }

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

bool UP4InventoryComponent::UseItem(UItemDataBase* ItemData)
{
    if (!ItemData) return false;

    // 1. 인벤토리에 아이템이 있는지 확인
    if (GetItemCount(ItemData) <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("아이템이 인벤토리에 없습니다!"));
        return false;
    }

    // 2. Owner의 AbilitySystemComponent 가져오기
    AActor* Owner = GetOwner();
    if (!Owner) return false;

    IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(Owner);
    if (!ASI) return false;

    UAbilitySystemComponent* ASC = ASI->GetAbilitySystemComponent();
    if (!ASC) return false;

    // 3. GameplayEffect 적용
    TSubclassOf<UGameplayEffect> Effect = ItemData->GetItemEffect();
    if (Effect)
    {
        FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
        EffectContext.AddSourceObject(ItemData);

        FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(Effect, 1.0f, EffectContext);
        if (SpecHandle.IsValid())
        {
            ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
            UE_LOG(LogTemp, Log, TEXT("아이템 효과 적용: %s"), *ItemData->GetItemName().ToString());
        }
    }

    // 4. 소비 아이템이면 수량 감소
    FGameplayTag ConsumableTag = FGameplayTag::RequestGameplayTag(FName("Item.Consumable"));
    if (ItemData->HasTag(ConsumableTag))
    {
        RemoveItem(ItemData, 1);
    }

    return true;
}

bool UP4InventoryComponent::EquipItem(UItemDataBase* ItemData)
{
    if (!ItemData) return false;

    // 장비 태그 확인
    FGameplayTag EquipmentTag = FGameplayTag::RequestGameplayTag(FName("Item.Equipment"));
    if (!ItemData->HasTag(EquipmentTag))
    {
        UE_LOG(LogTemp, Warning, TEXT("장비 아이템이 아닙니다!"));
        return false;
    }

    // 이미 착용 중인지 확인
    if (ActiveEquipmentEffects.Contains(ItemData))
    {
        UE_LOG(LogTemp, Warning, TEXT("이미 착용 중인 아이템입니다!"));
        return false;
    }

    // AbilitySystemComponent 가져오기
    AActor* Owner = GetOwner();
    IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(Owner);
    if (!ASI) return false;

    UAbilitySystemComponent* ASC = ASI->GetAbilitySystemComponent();
    if (!ASC) return false;

    // 패시브 효과 적용
    TSubclassOf<UGameplayEffect> PassiveEffect = ItemData->EquipmentPassiveEffect;
    if (PassiveEffect)
    {
        FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
        EffectContext.AddSourceObject(ItemData);

        FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(PassiveEffect, 1.0f, EffectContext);
        if (SpecHandle.IsValid())
        {
            FActiveGameplayEffectHandle EffectHandle = ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

            // 효과 핸들 저장 (나중에 해제할 때 사용)
            ActiveEquipmentEffects.Add(ItemData, EffectHandle);

            UE_LOG(LogTemp, Log, TEXT("장비 착용: %s"), *ItemData->GetItemName().ToString());
        }
    }

    return true;
}

bool UP4InventoryComponent::UnequipItem(UItemDataBase* ItemData)
{
    if (!ItemData) return false;

    // 착용 중인지 확인
    if (!ActiveEquipmentEffects.Contains(ItemData))
    {
        UE_LOG(LogTemp, Warning, TEXT("착용하지 않은 아이템입니다!"));
        return false;
    }

    // AbilitySystemComponent 가져오기
    AActor* Owner = GetOwner();
    IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(Owner);
    if (!ASI) return false;

    UAbilitySystemComponent* ASC = ASI->GetAbilitySystemComponent();
    if (!ASC) return false;

    // 효과 제거
    FActiveGameplayEffectHandle EffectHandle = ActiveEquipmentEffects[ItemData];
    ASC->RemoveActiveGameplayEffect(EffectHandle);

    ActiveEquipmentEffects.Remove(ItemData);

    UE_LOG(LogTemp, Log, TEXT("장비 해제: %s"), *ItemData->GetItemName().ToString());

    return true;
}

bool UP4InventoryComponent::HasSpace(UItemDataBase* ItemData) const
{
    if (!ItemData) return false;

    // 아이템 타입에 따라 슬롯 개수 확인
    FGameplayTag EquipmentTag = FGameplayTag::RequestGameplayTag(FName("Item.Equipment"));
    FGameplayTag ConsumableTag = FGameplayTag::RequestGameplayTag(FName("Item.Consumable"));

    int32 CurrentEquipCount = 0;
    int32 CurrentConsumCount = 0;

    for (const FInventoryItem& Item : InventoryItems)
    {
        if (Item.ItemData)
        {
            if (Item.ItemData->HasTag(EquipmentTag)) CurrentEquipCount++;
            else if (Item.ItemData->HasTag(ConsumableTag)) CurrentConsumCount++;
        }
    }

    if (ItemData->HasTag(EquipmentTag))
        return CurrentEquipCount < MaxEquipmentSlots;
    else if (ItemData->HasTag(ConsumableTag))
        return CurrentConsumCount < MaxConsumableSlots;

    return false;
}

int32 UP4InventoryComponent::GetItemCount(UItemDataBase* ItemData) const
{
    if (!ItemData) return 0;

    int32 TotalCount = 0;
    for (const FInventoryItem& Item : InventoryItems)
    {
        if (Item.ItemData == ItemData)
        {
            TotalCount += Item.Quantity;
        }
    }
    return TotalCount;
}




