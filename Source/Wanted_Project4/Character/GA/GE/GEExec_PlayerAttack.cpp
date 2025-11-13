// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GA/GE/GEExec_PlayerAttack.h"
#include "Attribute/P4PlayerAttributeSet.h"
#include "Monster/Stat/P4MonsterAttributeSet.h"
#include "Monster/P4MonsterBase.h"

// Attribute 캡처 구조체
struct FAttackStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackRate);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CurHP);
	//DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalChance);
	//DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalMultiplier);
	//DECLARE_ATTRIBUTE_CAPTUREDEF(Defense);

	FAttackStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UP4PlayerAttributeSet, AttackRate, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UP4MonsterAttributeSet, CurHP, Target, false);
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UP4PlayerAttributeSet, CriticalChance, Source, true);
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UP4PlayerAttributeSet, CriticalMultiplier, Source, true);
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UP4MonsterAttributeSet, Defense, Target, false);
	}
};

static FAttackStatics& AttackStatics()
{
	static FAttackStatics Statics;
	return Statics;
}


UGEExec_PlayerAttack::UGEExec_PlayerAttack()
{
	RelevantAttributesToCapture.Add(AttackStatics().AttackRateDef);
	RelevantAttributesToCapture.Add(AttackStatics().CurHPDef);
	//RelevantAttributesToCapture.Add(AttackStatics().CriticalMultiplierDef);
	//RelevantAttributesToCapture.Add(AttackStatics().DefenseDef);
	//RelevantAttributesToCapture.Add(AttackStatics().CurHPDef);
}

void UGEExec_PlayerAttack::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	//Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	float AttackPower = 0.f;
	float MonsterHp = 0.f;
	//float Defense = 0.f;
	//float CritChance = 0.f;
	//float CritMultiplier = 0.f;

	// Attribute 캡처
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(AttackStatics().AttackRateDef, {}, AttackPower);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(AttackStatics().CurHPDef, {}, MonsterHp);

	// --- 실제 계산 로직 ---


	// Target의 CurHP에 반영
	OutExecutionOutput.AddOutputModifier(
		FGameplayModifierEvaluatedData(AttackStatics().CurHPProperty, EGameplayModOp::Additive, -AttackPower)
	);
}
