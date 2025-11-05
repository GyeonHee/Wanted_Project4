// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "ItemDataBase.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_PROJECT4_API UItemDataBase : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
    /** PrimaryAssetId는 UPrimaryDataAsset일 때 필요 (AssetManager용) */
    virtual FPrimaryAssetId GetPrimaryAssetId() const override
    {
        return FPrimaryAssetId(GetClass()->GetFName(), GetFName());
    }

    /** 태그 확인용 헬퍼 함수 */
    UFUNCTION(BlueprintCallable, Category = "Item|Tags")
    bool HasTag(FGameplayTag Tag) const
    {
        return ItemTags.HasTag(Tag);
    }

    UFUNCTION(BlueprintCallable, Category = "Item|Tags")
    bool HasAnyTag(const FGameplayTagContainer& OtherTags) const
    {
        return ItemTags.HasAny(OtherTags);
    }

    UFUNCTION(BlueprintCallable, Category = "Item|Tags")
    bool HasAllTags(const FGameplayTagContainer& OtherTags) const
    {
        return ItemTags.HasAll(OtherTags);
    }

    // Getter
    FORCEINLINE FText GetItemName() const { return ItemName; }
    FORCEINLINE TSoftObjectPtr<UTexture2D> GetIcon() const { return Icon; }
    FORCEINLINE FGameplayTagContainer GetItemTags() const { return ItemTags; }
    FORCEINLINE int32 GetMaxStackCount() const { return MaxStackCount; }
protected:
    // 아이템 이름 (표시용)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    FText ItemName;

    // 아이템 아이콘
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    TSoftObjectPtr<UTexture2D> Icon;

    // 태그 (여기에 Item.Equipment.Weapon.Sword 같은걸 넣음)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Tags")
    FGameplayTagContainer ItemTags;

    // 스택 수량
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Stats")
    int32 MaxStackCount = 99;
};
