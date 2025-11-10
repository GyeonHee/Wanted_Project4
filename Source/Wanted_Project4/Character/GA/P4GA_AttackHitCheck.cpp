// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GA/P4GA_AttackHitCheck.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Character/GA/AT/P4AT_Trace.h"
#include "Character/GA/TA/P4TA_Trace.h"
#include "Attribute/P4PlayerAttributeSet.h"
#include "Monster/P4MonsterBase.h"
#include "Monster/Stat/P4MonsterAttributeSet.h"

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

		UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo_Checked();
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitResult.GetActor());
		if (!SourceASC || !TargetASC)
		{
			UE_LOG(LogTemp, Error, TEXT("ASC not found!"));
			return;
		}

		const UP4PlayerAttributeSet* SourceAttribute = SourceASC->GetSet<UP4PlayerAttributeSet>();
		UP4MonsterAttributeSet* TargetAttribute = const_cast<UP4MonsterAttributeSet*>(TargetASC->GetSet<UP4MonsterAttributeSet>());
		if (!SourceAttribute || !TargetAttribute)
		{
			UE_LOG(LogTemp, Error, TEXT("AttributeSet not found!"));
			return;
		}

		const float AttackDamage = SourceAttribute->GetAttackRate();
		// 수정 전: 몬스터 Attribute 에서 체력에 접근해서 HP 감소
		//TargetAttribute->SetCurHP(TargetAttribute->GetCurHP() - AttackDamage);

		// 수정 후: 인터페이스로 접근, 체력 감소 함수에 데미지를 인자로 넣어서 호출
		IP4MonsterDamageInterface* Monster = Cast<IP4MonsterDamageInterface>(TargetASC->GetOwner());
		Monster->MonsterApplyDamage(AttackDamage);
	}


	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
