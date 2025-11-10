// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "P4TA_Trace.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_PROJECT4_API AP4TA_Trace : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:
	AP4TA_Trace();

	virtual void StartTargeting(UGameplayAbility* Ability) override;

	virtual void ConfirmTargetingAndContinue() override;
	void SetShowDebug(bool InShowDebug) { bShowDebug = InShowDebug; }

protected:
	virtual FGameplayAbilityTargetDataHandle MakeTargetData() const;

	bool bShowDebug = false;
	
};
