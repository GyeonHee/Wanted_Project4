// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "P4ItemIconLoader.generated.h"

DECLARE_DELEGATE_OneParam(FOnIconLoadedDelegate, UTexture2D*);
/**
 * 
 */
UCLASS()
class WANTED_PROJECT4_API UP4ItemIconLoader : public UObject
{
	GENERATED_BODY()
	
public:
    // 비동기 로딩 시작
    void LoadIconAsync(TSoftObjectPtr<UTexture2D> Icon, FOnIconLoadedDelegate OnLoaded);

    // 즉시 로딩 (이미 로드됨)
    UTexture2D* GetLoadedIcon(TSoftObjectPtr<UTexture2D> Icon);

private:
    TMap<FSoftObjectPath, TWeakObjectPtr<UTexture2D>> CachedIcons;

};
