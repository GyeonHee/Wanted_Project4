// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/P4HpBarWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
//#include "Interface/P4CharacterWidgetInterface.h"
UP4HpBarWidget::UP4HpBarWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//MaxHp = -1.0f;
	CurrentHp = 70.0f;
	MaxHp = 100.0f;
}


void UP4HpBarWidget::UpdateHpBar(float NewCurrentHp)
{
	CurrentHp = NewCurrentHp;

	ensureAlways(MaxHp > 0.0f);

	if (HpProgressBar != nullptr)
	{
		HpProgressBar->SetPercent(CurrentHp / MaxHp);
	}
}

void UP4HpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//위젯 참조를 위한 코드 작성.
	HpProgressBar
		= Cast<UProgressBar>(
			GetWidgetFromName(TEXT("P4HpBar"))
		);

	ensureAlways(HpProgressBar);

	//IP4CharacterWidgetInterface* CharacterWidget
	//	= Cast<IP4CharacterWidgetInterface>(OwningActor);

	//if (CharacterWidget != nullptr)
	//{
	//	CharacterWidget->SetupCharacterWidget(this);
	//}
	
}
