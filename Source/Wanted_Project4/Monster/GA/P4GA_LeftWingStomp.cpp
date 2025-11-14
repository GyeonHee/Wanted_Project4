// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/GA/P4GA_LeftWingStomp.h"

#include "Monster/P4MonsterBase.h"

UP4GA_LeftWingStomp::UP4GA_LeftWingStomp()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.LeftWingStomp")));
}

void UP4GA_LeftWingStomp::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo,
                                          const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// @Todo: Ability 호출 확인
	UE_LOG(LogTemp, Log, TEXT("LeftWingStomp Ability 호출"));
	
	// 몬스터 베이스 캐스트
	AP4MonsterBase* Monster = Cast<AP4MonsterBase>(ActorInfo->AvatarActor.Get());
	if (Monster)
	{
		// 몽타주 실행
		UAnimMontage* LeftWingStompMontage = LoadObject<UAnimMontage>(
			nullptr,
			TEXT("")
		);
		if (LeftWingStompMontage)
		{
			Monster->PlayAnimMontage(LeftWingStompMontage);
		}
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
