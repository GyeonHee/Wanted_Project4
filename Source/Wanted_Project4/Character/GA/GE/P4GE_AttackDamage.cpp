// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GA/GE/P4GE_AttackDamage.h"
#include "Attribute/P4PlayerAttributeSet.h"

UP4GE_AttackDamage::UP4GE_AttackDamage()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;

	FGameplayModifierInfo HealthModifier;
	HealthModifier.Attribute = FGameplayAttribute(FindFieldChecked<FProperty>(UP4PlayerAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UP4PlayerAttributeSet, Health)));
	HealthModifier.ModifierOp = EGameplayModOp::Additive;

	FScalableFloat DamageAmount(-30.0f);
	FGameplayEffectModifierMagnitude ModMagnitude(DamageAmount);

	HealthModifier.ModifierMagnitude = ModMagnitude;
	Modifiers.Add(HealthModifier);
}
