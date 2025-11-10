// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GA/P4GA_AttackHitCheck.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Character/GA/AT/P4AT_Trace.h"
#include "Character/GA/TA/P4TA_Trace.h"

UP4GA_AttackHitCheck::UP4GA_AttackHitCheck()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UP4GA_AttackHitCheck::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UP4AT_Trace* AttackTraceTask = UP4AT_Trace::CreateTask(this, AP4TA_Trace::StaticClass());
	AttackTraceTask->OnComplete.AddDynamic(this, &UP4GA_AttackHitCheck::OnTraceResultCallback);
	AttackTraceTask->ReadyForActivation();

	UE_LOG(LogTemp, Log, TEXT("Begin"));
}

void UP4GA_AttackHitCheck::OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	if (UAbilitySystemBlueprintLibrary::TargetDataHasHitResult(TargetDataHandle, 0))
	{
		FHitResult HitResult = UAbilitySystemBlueprintLibrary::GetHitResultFromTargetData(TargetDataHandle, 0);
		UE_LOG(LogTemp, Log, TEXT("Target %s Detected"), *(HitResult.GetActor()->GetName()));
	}


	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
