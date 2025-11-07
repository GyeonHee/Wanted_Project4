// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/P4CustomWidget.h"
#include "GameplayTagContainer.h"
#include "P4InventoryComponent.h"
#include "P4Slot.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_PROJECT4_API UP4Slot : public UP4CustomWidget
{
	GENERATED_BODY()
	
public:
	UP4Slot(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void SetItem(const struct FInventoryItem& InItemData);

	void ClearSlot();
public:
	UPROPERTY(EditAnywhere, Category = "Slot")
	TObjectPtr<class UItemDataBase> ItemData;

	UPROPERTY(EditAnywhere, Category = "Slot")
	TObjectPtr<class UImage> IMG_Item;

	// 기본 빈 슬롯 텍스처
	UPROPERTY(EditAnywhere, Category = "Slot")
	TObjectPtr<class UTexture2D> DefaultTexture;

	UPROPERTY(EditAnywhere, Category = "Slot")
	TObjectPtr<class UTextBlock> TXT_Quantity;

	UPROPERTY(EditAnywhere, Category = "Slot")
	int32 SlotIndex;

protected:
	// 슬롯이 현재 가진 아이템 정보
	FInventoryItem CurrentItem;
};
