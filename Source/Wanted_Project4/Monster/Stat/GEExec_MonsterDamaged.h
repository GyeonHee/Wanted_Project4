// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEExec_MonsterDamaged.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_PROJECT4_API UGEExec_MonsterDamaged : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UGEExec_MonsterDamaged();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
