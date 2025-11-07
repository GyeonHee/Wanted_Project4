// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Stat/GEExec_MonsterDamaged.h"
#include "P4MonsterAttributeSet.h"

struct FDamagedStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageAmount);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CurHP);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxHP);

	FDamagedStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UP4MonsterAttributeSet, DamageAmount, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UP4MonsterAttributeSet, CurHP, Source, true);
		 DEFINE_ATTRIBUTE_CAPTUREDEF(UP4MonsterAttributeSet, MaxHP, Source, true);
	}
};

static const FDamagedStatics& DamagedStatics()
{
	static FDamagedStatics DamagedStatics;
	return DamagedStatics;
}


UGEExec_MonsterDamaged::UGEExec_MonsterDamaged()
{
	RelevantAttributesToCapture.Add(DamagedStatics().DamageAmountDef);
	RelevantAttributesToCapture.Add(DamagedStatics().CurHPDef);
	RelevantAttributesToCapture.Add(DamagedStatics().MaxHPDef);
}

void UGEExec_MonsterDamaged::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                    FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	float Damage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamagedStatics().DamageAmountDef,
		FAggregatorEvaluateParameters(),
		Damage
	);

	// 체력 감소 적용
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(
			DamagedStatics().CurHPProperty,
			EGameplayModOp::Additive,
			-Damage
		)
	);
	
	UE_LOG(LogTemp, Log, TEXT("Damage 적용: -%f"), Damage);
}
