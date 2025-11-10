// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/P4TestCharacter.h"
#include "UI/P4InventoryWidget.h"
#include "Inventory/P4InventoryComponent.h"
#include "Item/ItemDataBase.h"
#include "TimerManager.h"
#include "GameplayAbilities/Public/AbilitySystemComponent.h"

// Sets default values
AP4TestCharacter::AP4TestCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // 인벤토리 컴포넌트 생성
    InventoryComp = CreateDefaultSubobject<UP4InventoryComponent>(TEXT("InventoryComponent"));

    // AbilitySystemComponent 생성
    AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

// Called when the game starts or when spawned
void AP4TestCharacter::BeginPlay()
{
    Super::BeginPlay();

    // 테스트용 아이템 추가 (UI는 컨트롤러가 담당)
    if (InventoryComp)
    {
        UItemDataBase* TestSword = LoadObject<UItemDataBase>(nullptr,
            TEXT("/Game/Item/Equipment/DA_Sword.DA_Sword"));
        UItemDataBase* TestShield = LoadObject<UItemDataBase>(nullptr,
            TEXT("/Game/Item/Equipment/DA_Shield.DA_Shield"));
        UItemDataBase* TestPotion = LoadObject<UItemDataBase>(nullptr,
            TEXT("/Game/Item/Consumable/DA_HealthPotion.DA_HealthPotion"));
        UItemDataBase* TestPotion2 = LoadObject<UItemDataBase>(nullptr,
            TEXT("/Game/Item/Consumable/DA_ManaPotion.DA_ManaPotion"));

        if (TestSword)
        {
            InventoryComp->AddItem(TestSword, 1);
            UE_LOG(LogTemp, Warning, TEXT("검 추가됨!"));
            InventoryComp->AddItem(TestSword, 1);
            UE_LOG(LogTemp, Warning, TEXT("검 1개 더 추가됨!"));
            InventoryComp->AddItem(TestShield, 1);
        }

        if (TestPotion)
        {
            InventoryComp->AddItem(TestPotion, 10);
            UE_LOG(LogTemp, Warning, TEXT("포션 10개 추가됨!"));
            InventoryComp->AddItem(TestPotion, 5);
            UE_LOG(LogTemp, Warning, TEXT("포션 5개 더 추가됨!"));
            InventoryComp->AddItem(TestPotion, 99);
            InventoryComp->AddItem(TestPotion, 90);
            InventoryComp->AddItem(TestPotion2, 50);
        }
    }
}