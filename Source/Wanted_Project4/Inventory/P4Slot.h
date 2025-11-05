// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/P4CustomWidget.h"
#include "GameplayTagContainer.h"
#include "P4Slot.generated.h"

// 업데이트 델리게이트 선언
DECLARE_DELEGATE(FOnUpdateSlotDelegate);

// Wrapper 구조체 선언
USTRUCT(BlueprintType)
struct FUpdateSlotDelegateWrapper
{
	GENERATED_BODY()

	FUpdateSlotDelegateWrapper() {}
	FUpdateSlotDelegateWrapper(const FOnUpdateSlotDelegate& InSlotDelegate) : SlotDelegate(InSlotDelegate) {}

	FOnUpdateSlotDelegate SlotDelegate;
};

/**
 * 
 */
UCLASS()
class WANTED_PROJECT4_API UP4Slot : public UP4CustomWidget
{
	GENERATED_BODY()
	
public:
	// 슬롯 초기화 함수
	void Init();
	// 슬롯 업데이트 함수
	void UpdateSlot();

protected:
	virtual void NativeConstruct() override;

public:
	// 슬롯 이미지
	UPROPERTY(VisibleAnywhere, Category = "Slot", meta = (BindWidget = "true"))
	TObjectPtr<class UImage> IMG_Item;

	// 슬롯 아이템 수량
	UPROPERTY(VisibleAnywhere, Category = "Slot", meta = (BindWidget = "true"))
	TObjectPtr<class UTextBlock> TXT_Quantity;

	// 현재 슬롯의 인덱스
	UPROPERTY(EditAnywhere, Category = "Slot")
	int32 SlotIndex;

protected:
	// 빈 칸에 적용하기 위한 투명 테스쳐
	UPROPERTY(EditAnywhere, Category = "Slot")
	TObjectPtr<class UTexture2D> DefaultTexture;

	// 개별 슬롯 업데이트 함수
	void UpdateEquipmentSlot();
	void UpdateConsumableSlot();

	// 아이템 태그 별로 델리게이트 호출
	UPROPERTY()
	TMap<FGameplayTag, FUpdateSlotDelegateWrapper> SlotUpdateActions;
};
