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
	//if (UAbilitySystemBlueprintLibrary::TargetDataHasHitResult(TargetDataHandle, 0))
	//{
	//	FHitResult HitResult = UAbilitySystemBlueprintLibrary::GetHitResultFromTargetData(TargetDataHandle, 0);
	//	UE_LOG(LogTemp, Log, TEXT("Target %s Detected"), *(HitResult.GetActor()->GetName()));

	//	UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo_Checked();
	//	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitResult.GetActor());
	//	if (!SourceASC || !TargetASC)
	//	{
	//		UE_LOG(LogTemp, Error, TEXT("ASC not found!"));
	//		return;
	//	}

	//	const UP4PlayerAttributeSet* SourceAttribute = SourceASC->GetSet<UP4PlayerAttributeSet>();
	//	UP4MonsterAttributeSet* TargetAttribute = const_cast<UP4MonsterAttributeSet*>(TargetASC->GetSet<UP4MonsterAttributeSet>());
	//	if (!SourceAttribute || !TargetAttribute)
	//	{
	//		UE_LOG(LogTemp, Error, TEXT("AttributeSet not found!"));
	//		return;
	//	}

	//	const float AttackDamage = SourceAttribute->GetAttackRate();
	//	// 수정 전: 몬스터 Attribute 에서 체력에 접근해서 HP 감소
	//	//TargetAttribute->SetCurHP(TargetAttribute->GetCurHP() - AttackDamage);

	//	// 수정 후: 인터페이스로 접근, 체력 감소 함수에 데미지를 인자로 넣어서 호출
	//	IP4MonsterDamageInterface* Monster = Cast<IP4MonsterDamageInterface>(TargetASC->GetOwner());
	//	Monster->MonsterApplyDamage(AttackDamage);
	//}


	//bool bReplicatedEndAbility = true;
	//bool bWasCancelled = false;
	//EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);


	// todo: 알아먹게 고치기
	int32 NumData = TargetDataHandle.Data.Num();
	if (NumData == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No target data found."));
		return;
	}

	UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo_Checked();
	const UP4PlayerAttributeSet* SourceAttribute = SourceASC->GetSet<UP4PlayerAttributeSet>();

	if (!SourceASC || !SourceAttribute)
	{
		UE_LOG(LogTemp, Error, TEXT("Source ASC or Attribute not found!"));
		return;
	}

	const float AttackDamage = SourceAttribute->GetAttackRate();

	// 여러 타겟 순회
	for (int32 i = 0; i < NumData; ++i)
	{
		if (!UAbilitySystemBlueprintLibrary::TargetDataHasHitResult(TargetDataHandle, i))
			continue;

		FHitResult HitResult = UAbilitySystemBlueprintLibrary::GetHitResultFromTargetData(TargetDataHandle, i);
		AActor* HitActor = HitResult.GetActor();

		if (!HitActor || HitActor == GetAvatarActorFromActorInfo())
			continue;

		UE_LOG(LogTemp, Log, TEXT("Target %s Detected"), *HitActor->GetName());

		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitActor);
		if (!TargetASC)
		{
			UE_LOG(LogTemp, Warning, TEXT("Target ASC not found for %s"), *HitActor->GetName());
			continue;
		}

		// AttributeSet 접근 (몬스터용)
		//UP4MonsterAttributeSet* TargetAttribute = const_cast<UP4MonsterAttributeSet*>(TargetASC->GetSet<UP4MonsterAttributeSet>());
		//if (!TargetAttribute)
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("Monster AttributeSet not found for %s"), *HitActor->GetName());
		//	continue;
		//}

		// 인터페이스 기반 데미지 처리
		if (IP4MonsterDamageInterface* Monster = Cast<IP4MonsterDamageInterface>(HitActor))
		{
			Monster->MonsterApplyDamage(AttackDamage);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s does not implement MonsterDamageInterface"), *HitActor->GetName());
		}
	}

	// Ability 종료 처리
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
