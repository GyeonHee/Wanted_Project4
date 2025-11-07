// Fill out your copyright notice in the Description page of Project Settings.


#include "P4CharacterBase.h"
#include "AbilitySystemComponent.h"
#include "Attribute/P4PlayerAttributeSet.h"

// Sets default values
AP4CharacterBase::AP4CharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// GAS 초기화
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
}

void AP4CharacterBase::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    if (ASC)
    {
        ASC->InitAbilityActorInfo(this, this);
        AttributeSet = NewObject<UP4PlayerAttributeSet>(this, UP4PlayerAttributeSet::StaticClass());

        //// 기본 어빌리티 바로 등록
        //ASC->GiveAbility(FGameplayAbilitySpec(UBasicAttackAbility::StaticClass()));
        //ASC->GiveAbility(FGameplayAbilitySpec(UDodgeAbility::StaticClass()));
        //ASC->GiveAbility(FGameplayAbilitySpec(USkillAbility::StaticClass()));
    }
}

UAbilitySystemComponent* AP4CharacterBase::GetAbilitySystemComponent() const
{
	return ASC;
}

void AP4CharacterBase::AttackHitCheck()
{
	// 충돌 판정 로직 작성.
}


