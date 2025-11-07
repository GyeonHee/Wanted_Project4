// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GA/P4GA_Attack.h"
#include "Character/P4CharacterBase.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
//#include "ArenaBattleGAS.h"
#include "GameFramework/CharacterMovementComponent.h"
//#include "Character/ABComboActionData.h"

UP4GA_Attack::UP4GA_Attack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UP4GA_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AP4CharacterBase* P4Character = CastChecked<AP4CharacterBase>(ActorInfo->AvatarActor.Get());
	//CurrentComboData = P4Character->GetComboActionData();
	P4Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	if (P4Character->GetComboActionMontage())
	{
		UAbilityTask_PlayMontageAndWait* PlayAttackTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayAttack"), P4Character->GetComboActionMontage());
		PlayAttackTask->OnCompleted.AddDynamic(this, &UP4GA_Attack::OnCompleteCallback);
		PlayAttackTask->OnInterrupted.AddDynamic(this, &UP4GA_Attack::OnInterruptedCallback);
		PlayAttackTask->ReadyForActivation();
	}
		

	//StartComboTimer();
}

void UP4GA_Attack::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	UE_LOG(LogTemp, Log, TEXT("InputPressed"));
	//if (!ComboTimerHandle.IsValid())
	//{
	//	HasNextComboInput = false;
	//}
	//else
	//{
	//	HasNextComboInput = true;
	//}
}

void UP4GA_Attack::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UP4GA_Attack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	AP4CharacterBase* P4Character = CastChecked<AP4CharacterBase>(ActorInfo->AvatarActor.Get());
	P4Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	//CurrentComboData = nullptr;
	//CurrentCombo = 0;
	//HasNextComboInput = false;
}

void UP4GA_Attack::OnCompleteCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UP4GA_Attack::OnInterruptedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
