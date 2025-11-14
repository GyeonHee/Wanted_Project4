// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GA/GE/GEExec_PlayerDamaged.h"
#include "Attribute/P4PlayerAttributeSet.h"

// Attribute 캡처 구조체
struct FStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageAmount);
	//DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalChance);
	//DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalMultiplier);
	//DECLARE_ATTRIBUTE_CAPTUREDEF(Defense);

	FStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UP4PlayerAttributeSet, Health, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UP4PlayerAttributeSet, DamageAmount, Source, true);
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UP4PlayerAttributeSet, CriticalChance, Source, true);
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UP4PlayerAttributeSet, CriticalMultiplier, Source, true);
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UP4MonsterAttributeSet, Defense, Target, false);
	}
};

static FStatics& DamageStatics()
{
	static FStatics Statics;
	return Statics;
}

UGEExec_PlayerDamaged::UGEExec_PlayerDamaged()
{
	RelevantAttributesToCapture.Add(DamageStatics().HealthDef);
	RelevantAttributesToCapture.Add(DamageStatics().DamageAmountDef);
}

void UGEExec_PlayerDamaged::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	float PlayerHp = 0.f;
	float Damage = 0.f;

	// Attribute 캡처
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().HealthDef, {}, PlayerHp);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DamageAmountDef, {}, Damage);

	// --- 실제 계산 로직 ---

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().DamageAmountDef,
		FAggregatorEvaluateParameters(),
		Damage
	);

	// Target의 CurHP에 반영
	OutExecutionOutput.AddOutputModifier(
		FGameplayModifierEvaluatedData(DamageStatics().HealthProperty, EGameplayModOp::Additive, -Damage)
	);
}
