// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/P4PlayerState.h"
#include "AbilitySystemComponent.h"
#include "Attribute/P4PlayerAttributeSet.h"

AP4PlayerState::AP4PlayerState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	//ASC->SetIsReplicated(true);
	AttributeSet = CreateDefaultSubobject<UP4PlayerAttributeSet>(TEXT("AttributeSet"));
	//SkillAttributeSet = CreateDefaultSubobject<UP4SkillAttributeSet>(TEXT("SkillAttributeSet"));
}

UAbilitySystemComponent* AP4PlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}