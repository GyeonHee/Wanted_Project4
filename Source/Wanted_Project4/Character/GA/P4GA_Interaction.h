// Fill out your copyright notice in the Description page of Project Settings.
/**
* 작성: 한승헌
* 일시: 2025-11-12
* 내용: NPC등 기타 물건과 상호작용하는 코드입니다.
* 
**/
#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "P4GA_Interaction.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_PROJECT4_API UP4GA_Interaction : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UP4GA_Interaction();


public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:

protected:
	
};
