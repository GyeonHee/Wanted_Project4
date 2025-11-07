// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/P4ItemIconLoader.h"
#include "Engine/Texture2D.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

void UP4ItemIconLoader::LoadIconAsync(TSoftObjectPtr<UTexture2D> Icon, FOnIconLoadedDelegate OnLoaded)
{
    if (Icon.IsNull())
    {
        OnLoaded.ExecuteIfBound(nullptr);
        return;
    }

    // 이미 로드됨
    if (Icon.IsValid())
    {
        CachedIcons.Add(Icon.ToSoftObjectPath(), Icon.Get());
        OnLoaded.ExecuteIfBound(Icon.Get());
        return;
    }

    // 캐시 확인
    if (TWeakObjectPtr<UTexture2D>* Cached = CachedIcons.Find(Icon.ToSoftObjectPath()))
    {
        if (Cached->IsValid())
        {
            OnLoaded.ExecuteIfBound(Cached->Get());
            return;
        }
    }

    // 비동기 로딩
    FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
    Streamable.RequestAsyncLoad(
        Icon.ToSoftObjectPath(),
        FStreamableDelegate::CreateWeakLambda(this, [this, Icon, OnLoaded]()
            {
                if (UTexture2D* LoadedIcon = Icon.Get())
                {
                    CachedIcons.Add(Icon.ToSoftObjectPath(), LoadedIcon);
                    OnLoaded.ExecuteIfBound(LoadedIcon);
                }
                else
                {
                    OnLoaded.ExecuteIfBound(nullptr);
                }
            })
    );
}

UTexture2D* UP4ItemIconLoader::GetLoadedIcon(TSoftObjectPtr<UTexture2D> Icon)
{
    if (Icon.IsValid())
        return Icon.Get();

    if (TWeakObjectPtr<UTexture2D>* Cached = CachedIcons.Find(Icon.ToSoftObjectPath()))
    {
        return Cached->Get();
    }

    return nullptr;
}
