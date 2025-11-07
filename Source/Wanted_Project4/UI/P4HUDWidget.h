// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "P4HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_PROJECT4_API UP4HUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UP4HUDWidget(const FObjectInitializer& ObjectInitalizer);

	void UpdateHpBar(float NewCurrentHp);

	void UpdataMiniMap(FVector PlayerLocation);


protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	TObjectPtr<class UP4HpBarWidget> HpBar;

	//UPROPERTY()
	//TObjectPtr<class UP4MiniMapWidget> MiniMap;
};
