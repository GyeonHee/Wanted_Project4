// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/P4HUDWidget.h"
#include "P4HpBarWidget.h"
#include "P4MiniMapWidget.h"
#include "Interface/P4CharacterHUDInterface.h"

UP4HUDWidget::UP4HUDWidget(const FObjectInitializer& ObjectInitalizer)
	:Super(ObjectInitalizer)
{

}

//작성 한승헌 GAS사용시 이건 필요가 없음
//void UP4HUDWidget::UpdateHpBar(float NewCurrentHp)
//{
//	HpBar->UpdateHpBar(NewCurrentHp);
//}

void UP4HUDWidget::UpdataMiniMap(FVector PlayerLocation)
{

}

void UP4HUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//데이터 연동.
	HpBar =  Cast<UP4HpBarWidget>(
		GetWidgetFromName(TEXT("WidgetHpBar"))
	);

	ensureAlways(HpBar != nullptr);


	if (HpBar != nullptr && GetOwningPlayer() != nullptr)
	{
		APawn* Pawn = GetOwningPlayer()->GetPawn();

		if (Pawn != nullptr)
		{
			HpBar->SetAbilitySystemComponent(Pawn);
		}
	}

	//MiniMap = Cast<UP4MiniMapWidget>(
	//	GetWidgetFromName(TEXT("WidgetMiniMap"))
	//);

	//ensureAlways(MiniMap);

	//IP4CharacterHUDInterface* HUDPawn
	//	= Cast<IP4CharacterHUDInterface>(GetOwningPlayer()->GetPawn());

	//if (HUDPawn != nullptr)
	//{
	//	HUDPawn->SetupHUDWidget(this);
	//}

}
