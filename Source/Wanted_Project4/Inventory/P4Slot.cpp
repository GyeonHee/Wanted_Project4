// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/P4Slot.h"
#include "Item/ItemDataBase.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/AssetManager.h"
#include "UI/P4ItemIconLoader.h"
#include "Inventory/P4InventoryComponent.h"
#include "Inventory/P4InventoryTags.h"
#include "Test/P4TestPlayerController.h"

#include "Blueprint/DragDropOperation.h"
#include "Layout/Geometry.h"
#include "Input/Events.h"


UP4Slot::UP4Slot(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}


void UP4Slot::NativeConstruct()
{
	Super::NativeConstruct();

	IMG_Item = Cast<UImage>(GetWidgetFromName(TEXT("IMG_Item")));
	ensureAlways(IMG_Item);

	TXT_Quantity = Cast<UTextBlock>(GetWidgetFromName(TEXT("TXT_Quantity")));
	ensureAlways(TXT_Quantity);
}

FReply UP4Slot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply Reply;
	Reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	// 우클릭 입력
	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		// 정보 체크용
		bool Success = false;
		UE_LOG(LogTemp, Log, TEXT("우클릭"));

		// 해당 슬롯에 아이템 정보가 존재하는지 체크
		if (CurrentItem.ItemData)
		{
			UE_LOG(LogTemp, Log, TEXT("아이템 있음: %s, 수량: %d"),
				*CurrentItem.ItemData->GetItemName().ToString(),
				CurrentItem.Quantity);

			// 잘못된 접근 방법
			//UP4InventoryComponent InvComp;

			// 올바른 접근 방법
			if (APlayerController* PC = GetOwningPlayer())
			{
				UE_LOG(LogTemp, Log, TEXT("[1] 플레이어 컨트롤러 찾음: %s"), *PC->GetName());
				if (APawn* Pawn = PC->GetPawn())
				{
					UE_LOG(LogTemp, Log, TEXT("[2] 폰 찾음: %s"), *Pawn->GetName());
					if (UP4InventoryComponent* InvComp = Pawn->FindComponentByClass<UP4InventoryComponent>())
					{
						UE_LOG(LogTemp, Log, TEXT("[3] 인벤토리 컴포넌트 찾음"));
						UE_LOG(LogTemp, Log, TEXT(" -> Owner: %s"), InvComp->GetOwner() ? *InvComp->GetOwner()->GetName() : TEXT("None"));

						if (CurrentItem.ItemData->HasTag(P4InventoryTags::Item::Equipment))
						{
							InvComp->EquipItem(CurrentItem.ItemData);
						}
						else if (CurrentItem.ItemData->HasTag(P4InventoryTags::Item::Consumable))
						{
							InvComp->UseItem(CurrentItem.ItemData);
						}
					}
					else
					{
						UE_LOG(LogTemp, Error, TEXT("[3] ❌ 인벤토리 컴포넌트를 찾지 못함"));
					}
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("[2] ❌ 폰을 찾지 못함"));
				}
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("[1] ❌ 플레이어 컨트롤러를 찾지 못함"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("아이템 없음"));
		}
	}
	return Reply.NativeReply;
}

void UP4Slot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
}

bool UP4Slot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	return false;
}

void UP4Slot::SetItem(const FInventoryItem& InItemData)
{
	UE_LOG(LogTemp, Warning, TEXT("슬롯 SetItem 호출됨"));

	CurrentItem = InItemData;

	// 아이템이 없으면 빈 슬롯 표시
	if (!InItemData.ItemData)
	{
		IMG_Item->SetBrushFromTexture(DefaultTexture);
		TXT_Quantity->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	// IconLoader 생성 
	if (!IconLoader)
	{
		IconLoader = NewObject<UP4ItemIconLoader>(this);
	}

	// 아이콘 비동기 로딩
	TSoftObjectPtr<UTexture2D> Icon = InItemData.ItemData->GetIcon();
	IconLoader->LoadIconAsync(Icon, FOnIconLoadedDelegate::CreateWeakLambda(this, [this](UTexture2D* LoadedIcon)
		{
			if (LoadedIcon)
			{
				IMG_Item->SetBrushFromTexture(LoadedIcon);
			}
			else
			{
				IMG_Item->SetBrushFromTexture(DefaultTexture);
			}
		}));

	// 수량 표시
	if (InItemData.Quantity > 1)
	{
		TXT_Quantity->SetText(FText::AsNumber(InItemData.Quantity));
		TXT_Quantity->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		// 수량이 1개 미만일 때에는 표시 안함
		TXT_Quantity->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UP4Slot::ClearSlot()
{
	CurrentItem = FInventoryItem();
	IMG_Item->SetBrushFromTexture(DefaultTexture);

	// 수량 텍스트도 숨기기
	if (TXT_Quantity)
	{
		TXT_Quantity->SetVisibility(ESlateVisibility::Hidden);
	}
}


