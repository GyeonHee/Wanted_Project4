// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GA/GE/GEExec_PlayerSuicide.h"
#include "GEExec_PlayerSuicide.h"
#include "Attribute/P4PlayerAttributeSet.h"

struct FSuicideStatics
{
    DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
    //DECLARE_ATTRIBUTE_CAPTUREDEF(MaxHP);

    FSuicideStatics()
    {
        DEFINE_ATTRIBUTE_CAPTUREDEF(UP4PlayerAttributeSet, Health, Source, false);
        //DEFINE_ATTRIBUTE_CAPTUREDEF(UP4PlayerAttributeSet, MaxHP, Target, false);
    }
};

static const FSuicideStatics& SuicideStatics()
{
    static FSuicideStatics Statics;
    return Statics;
}


UGEExec_PlayerSuicide::UGEExec_PlayerSuicide()
{
    RelevantAttributesToCapture.Add(SuicideStatics().HealthDef);
    //RelevantAttributesToCapture.Add(SuicideStatics().MaxHPDef);
}

void UGEExec_PlayerSuicide::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    //float CurrentHP = 0.f;
    //ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
    //    SuicideStatics().HealthDef,
    //    {},
    //    CurrentHP
    //);

    // HP를 무조건 0으로 만들기
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(
        SuicideStatics().HealthProperty,
        EGameplayModOp::Override,
        0.f
    ));
}
