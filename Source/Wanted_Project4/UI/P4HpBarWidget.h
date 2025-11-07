// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/P4CustomWidget.h"
#include "P4HpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_PROJECT4_API UP4HpBarWidget : public UP4CustomWidget
{
	GENERATED_BODY()

//Function Sections
public:
	UP4HpBarWidget(const FObjectInitializer& ObjectInitializer);


	void UpdateStat();

	void UpdateHpBar(float NewCurrentHp);
protected:
	// 위젯이 모두 초기화가 된 후에 호출되는 함수.
	// 위젯을 참조할 때 생성됐다는 것을 보장 받을 수 있음.
	virtual void NativeConstruct() override;


//Var Sections
public:

protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> HpProgressBar;

	UPROPERTY()
	float CurrentHp = 70.0f; //플레이어 캐릭터의 현재 체력.

	UPROPERTY()
	float MaxHp; //플레이어 캐릭터의 최대 체력.
};
