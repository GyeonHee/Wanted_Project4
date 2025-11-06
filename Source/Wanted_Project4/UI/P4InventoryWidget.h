// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/P4CustomWidget.h"
#include "GameplayTagContainer.h"
#include "P4InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_PROJECT4_API UP4InventoryWidget : public UP4CustomWidget
{
	GENERATED_BODY()

public:
	UP4InventoryWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeConstruct() override;

	// 인벤토리 컴포넌트랑 바인드
	void BindInventory(class UP4InventoryComponent* InInventoryComp);

	// UI 업데이트
	void RefreshUI();

public:
	// 인벤토리 컴포넌트로 인벤토리 데이터 참조
	UPROPERTY()
	TObjectPtr<class UP4InventoryComponent> InventoryComp;

protected:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TArray<TObjectPtr<class UP4Slot>> EquipmentSlots;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	TArray<TObjectPtr<class UP4Slot>> ConsumableSlots;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUniformGridPanel> EquipmentTypeSlot;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUniformGridPanel> ConsumableTypeSlot;

	
};

