// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/P4Slot.h"
#include "Item/ItemDataBase.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/AssetManager.h"

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

void UP4Slot::SetItem(const FInventoryItem& InItemData)
{
	UE_LOG(LogTemp, Warning, TEXT("슬롯 SetItem 호출됨"));

	CurrentItem = InItemData;

	if (!InItemData.ItemData)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemDataAsset이 nullptr - 기본 텍스처 사용"));
		IMG_Item->SetBrushFromTexture(DefaultTexture);
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("아이템: %s, 수량: %d"),
		*InItemData.ItemData->GetItemName().ToString(), InItemData.Quantity);

	TSoftObjectPtr<UTexture2D> SoftIcon = InItemData.ItemData->GetIcon();
	if (SoftIcon.IsNull())
	{
		IMG_Item->SetBrushFromTexture(DefaultTexture);
		return;
	}

	// 이미 로드된 상태면 바로 사용
	if (SoftIcon.IsValid())
	{
		IMG_Item->SetBrushFromTexture(SoftIcon.Get());
		return;
	}

	// 아직 로드 안 되었으면 기본 텍스처로 표시 후 비동기로 로드
	IMG_Item->SetBrushFromTexture(DefaultTexture);

	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
	Streamable.RequestAsyncLoad(
		SoftIcon.ToSoftObjectPath(),
		FStreamableDelegate::CreateWeakLambda(this, [this, SoftIcon]()
			{
				if (UTexture2D* LoadedIcon = SoftIcon.Get())
				{
					IMG_Item->SetBrushFromTexture(LoadedIcon);
				}
			})
	);

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


