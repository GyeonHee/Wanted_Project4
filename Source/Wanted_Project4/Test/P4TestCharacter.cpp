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

    // 테스트용 아이템 추가
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

    // 로컬 플레이어만 UI 생성 (약간의 딜레이)
    if (IsLocallyControlled())
    {
        // 다음 프레임에 위젯 생성 시도
        GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
            {
                CreateInventoryWidget();
            });
    }
}

void AP4TestCharacter::CreateInventoryWidget()
{
    UE_LOG(LogTemp, Warning, TEXT("=== CreateInventoryWidget 호출됨 ==="));

    if (!InventoryWidgetClass)
    {
        UE_LOG(LogTemp, Error, TEXT("InventoryWidgetClass가 설정되지 않음!"));
        return;
    }

    APlayerController* PC = Cast<APlayerController>(GetController());
    if (!PC)
    {
        UE_LOG(LogTemp, Error, TEXT("PlayerController를 가져올 수 없음! 재시도합니다..."));

        // 실패하면 0.1초 후 재시도
        FTimerHandle RetryTimerHandle;
        GetWorld()->GetTimerManager().SetTimer(RetryTimerHandle, [this]()
            {
                CreateInventoryWidget();
            }, 0.1f, false);
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT(" PlayerController 획득: %s"), *PC->GetName());

    // CreateWidget 타입을 UUserWidget으로
    UUserWidget* CreatedWidget = CreateWidget<UUserWidget>(PC, InventoryWidgetClass);
    if (!CreatedWidget)
    {
        UE_LOG(LogTemp, Error, TEXT(" 위젯 생성 실패!"));
        return;
    }

    // P4InventoryWidget으로 캐스팅
    InventoryWidgetInstance = Cast<UP4InventoryWidget>(CreatedWidget);
    if (!InventoryWidgetInstance)
    {
        UE_LOG(LogTemp, Error, TEXT(" P4InventoryWidget으로 캐스팅 실패!"));
        UE_LOG(LogTemp, Error, TEXT("   위젯 클래스: %s"), *CreatedWidget->GetClass()->GetName());
        UE_LOG(LogTemp, Error, TEXT("WBP_Inventory의 부모 클래스를 P4InventoryWidget으로 Reparent 해야합니다!"));
            return;
    }

    UE_LOG(LogTemp, Warning, TEXT(" 인벤토리 위젯 생성 성공"));

    InventoryWidgetInstance->AddToViewport();
    InventoryWidgetInstance->SetVisibility(ESlateVisibility::Hidden);

    // 바로 연결!
    InventoryWidgetInstance->BindInventory(InventoryComp);
    UE_LOG(LogTemp, Warning, TEXT(" 인벤토리 위젯 연결 완료"));
}

void AP4TestCharacter::ToggleInventory()
{
    if (!InventoryWidgetInstance)
    {
        UE_LOG(LogTemp, Error, TEXT(" InventoryWidgetInstance가 nullptr!"));
        return;
    }

    bIsInventoryVisible = !bIsInventoryVisible;

    APlayerController* PC = Cast<APlayerController>(GetController());
    if (!PC) return;

    if (bIsInventoryVisible)
    {
        InventoryWidgetInstance->SetVisibility(ESlateVisibility::Visible);
        PC->bShowMouseCursor = true;

        FInputModeGameAndUI InputMode;
        InputMode.SetWidgetToFocus(InventoryWidgetInstance->TakeWidget());
        InputMode.SetHideCursorDuringCapture(false);
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        PC->SetInputMode(InputMode);

        UE_LOG(LogTemp, Warning, TEXT("인벤토리 열림"));
    }
    else
    {
        InventoryWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
        PC->bShowMouseCursor = false;

        FInputModeGameOnly InputMode;
        PC->SetInputMode(InputMode);

        UE_LOG(LogTemp, Warning, TEXT("인벤토리 닫힘"));
    }
}