// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "P4InventoryComponent.h"
#include "P4Slot.h"
#include "P4ItemDragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_PROJECT4_API UP4ItemDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
	
public:
    // 슬롯 데이터 (드래그 중 어떤 아이템을 들고 있는지)
    UPROPERTY(BlueprintReadWrite, Category = "DragDrop")
    FInventoryItem DraggedItem;

    // 원래 슬롯 (드래그 시작 슬롯)
    UPROPERTY(BlueprintReadWrite, Category = "DragDrop")
    TObjectPtr<class UP4Slot> FromSlot;
};
