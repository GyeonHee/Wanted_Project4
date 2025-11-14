// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GA/P4GA_Death.h"
#include "Character/P4CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

UP4GA_Death::UP4GA_Death()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UP4GA_Death::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UE_LOG(LogTemp, Log, TEXT("FUCKFUNCKCUNFCKU"))
	AP4CharacterBase* P4Character = CastChecked<AP4CharacterBase>(ActorInfo->AvatarActor.Get());

	//P4Character->GetAbilitySystemComponent()->AddLooseGameplayTag(P4TAG_CHARACTER_ISDEAD);
	// 움직임 차단
	P4Character->GetCharacterMovement()->SetMovementMode(MOVE_None);
	// 콜리전 삭제
	P4Character->SetActorEnableCollision(false);
}

void UP4GA_Death::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
