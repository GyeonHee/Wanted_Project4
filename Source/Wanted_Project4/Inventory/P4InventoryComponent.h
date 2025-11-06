// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item/ItemDataBase.h"
#include "P4InventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnInventoryUpdated);

USTRUCT()
struct FInventoryItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UItemDataBase> ItemData;

	UPROPERTY(EditAnywhere)
	int32 Quantity = 0;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WANTED_PROJECT4_API UP4InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UP4InventoryComponent();

public:
	// 아이템 추가 함수
	bool AddItem(UItemDataBase* ItemData, int32 Quantity);

	// 아이템 제거 함수
	bool RemoveItem(UItemDataBase* ItemData, int32 Quantity);

	// 인벤토리 데이터 가져오기
	const TArray<FInventoryItem>& GetInventoryItems() const { return InventoryItems; }

	// 인벤토리가 변경되었을 때 알림을 보내는 델리게이트
	FOnInventoryUpdated OnInventoryUpdated;

protected:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TArray<FInventoryItem> InventoryItems;

};
