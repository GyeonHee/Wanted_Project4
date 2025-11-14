// Fill out your copyright notice in the Description page of Project Settings.


#include "P4GA_Interaction.h"
#include "UI/P4QuestWidget.h"
#include "Character/P4CharacterPlayer.h"
#include "NPC/P4NPCBase.h"

UP4GA_Interaction::UP4GA_Interaction()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UP4GA_Interaction::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UE_LOG(LogTemp, Display, TEXT("Check"));

	UE_LOG(LogTemp, Warning, TEXT("IsLocallyControlled: %s"),
		ActorInfo->IsLocallyControlled() ? TEXT("TRUE") : TEXT("FALSE"));

	// 로컬 플레이어에서만 UI 생성
	if (ActorInfo->IsLocallyControlled() == false)
	{
		UE_LOG(LogTemp, Display, TEXT("로컬플레이어부분오류"));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	
	//캐릭터 가져오기.
	AP4CharacterPlayer* PlayerCharacter 
		= Cast<AP4CharacterPlayer>(ActorInfo->AvatarActor.Get());

	if (PlayerCharacter != nullptr)
	{
		//NPC 가져오기.
		AP4NPCBase* NPC_Character 
			= Cast<AP4NPCBase>(PlayerCharacter->CurrentInteractActor);

		if (NPC_Character == nullptr)
		{	
			UE_LOG(LogTemp, Display, TEXT("NPCCharacter NULLPTR"));
			return;
		}

		NPC_Character->ShowQuestUI(NPC_Character->GetNPCQuestCode());
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UP4GA_Interaction::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	//필요하면 구현.
}

void UP4GA_Interaction::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	//필요하면 구현.
}

void UP4GA_Interaction::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility,bWasCancelled);
}
