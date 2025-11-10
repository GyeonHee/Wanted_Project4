// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/P4HpBarWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "AbilitySystemComponent.h"
#include "Attribute/P4PlayerAttributeSet.h"
//#include "Interface/P4CharacterWidgetInterface.h"
UP4HpBarWidget::UP4HpBarWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//MaxHp = -1.0f;
	CurrentHp = 70.0f;
	MaxHp = 100.0f;
}

void UP4HpBarWidget::UpdateHpBar()
{
	//CurrentHp = NewCurrentHp;

	ensureAlways(MaxHp > 0.0f);

	if (P4HpBar != nullptr)
	{
		P4HpBar->SetPercent(CurrentHp / MaxHp);
	}

}

void UP4HpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//위젯 참조를 위한 코드 작성.
	P4HpBar
		= Cast<UProgressBar>(
			GetWidgetFromName(TEXT("P4HpBar"))
		);

	ensureAlways(P4HpBar != nullptr);

	//IP4CharacterWidgetInterface* CharacterWidget
	//	= Cast<IP4CharacterWidgetInterface>(OwningActor);

	//if (CharacterWidget != nullptr)
	//{
	//	CharacterWidget->SetupCharacterWidget(this);
	//}
	
}

void UP4HpBarWidget::SetAbilitySystemComponent(AActor* InOwner)
{
	Super::SetAbilitySystemComponent(InOwner);



	if (ASC != nullptr)
	{
		const UP4PlayerAttributeSet* Attr = ASC->GetSet<UP4PlayerAttributeSet>();
		if (!IsValid(Attr)) return; // 아직 AttributeSet 안붙은 타이밍이면 그냥 패스

		ASC->GetGameplayAttributeValueChangeDelegate(UP4PlayerAttributeSet::GetHealthAttribute()).AddUObject(this,&UP4HpBarWidget::OnHealthChanged);
		ASC->GetGameplayAttributeValueChangeDelegate(UP4PlayerAttributeSet::GetMaxHealthAttribute()).AddUObject(this,&UP4HpBarWidget::OnMaxHealthChanged);

		const UP4PlayerAttributeSet* CurrentAttributeSet = ASC->GetSet<UP4PlayerAttributeSet>();

		ensure(CurrentAttributeSet);

		MaxHp = CurrentAttributeSet->GetMaxHealth();
		CurrentHp =  CurrentAttributeSet->GetHealth();

		ensure(MaxHp > 0.0f);

	}
}

void UP4HpBarWidget::OnHealthChanged(const FOnAttributeChangeData& ChangedData)
{
	CurrentHp = ChangedData.NewValue;
	UpdateHpBar();
}

void UP4HpBarWidget::OnMaxHealthChanged(const FOnAttributeChangeData& ChangedData)
{
	MaxHp = ChangedData.NewValue;
	UpdateHpBar();
}
