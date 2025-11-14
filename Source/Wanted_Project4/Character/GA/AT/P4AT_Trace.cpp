// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GA/AT/P4AT_Trace.h"
#include "Character/GA/TA/P4TA_Trace.h"
#include "AbilitySystemComponent.h"

UP4AT_Trace::UP4AT_Trace()
{
}

UP4AT_Trace* UP4AT_Trace::CreateTask(UGameplayAbility* OwningAbility, TSubclassOf<AP4TA_Trace> TargetActorClass)
{
	//AbilityTask_Trace 생성 (UP4AT_Trace)
	UP4AT_Trace* NewTask = NewAbilityTask<UP4AT_Trace>(OwningAbility);
	NewTask->TargetActorClass = TargetActorClass;
	return NewTask;
}

void UP4AT_Trace::Activate()
{
	Super::Activate();

	SpawnAndInitializeTargetActor();
	FinalizeTargetActor();

	SetWaitingOnAvatar();
}

void UP4AT_Trace::OnDestroy(bool AbilityEnded)
{
	if (SpawnedTargetActor)
	{
		SpawnedTargetActor->Destroy();
	}

	Super::OnDestroy(AbilityEnded);
}

void UP4AT_Trace::SpawnAndInitializeTargetActor()
{
	// TargetActor_Trace 스폰(AP4TA_Trace)
	SpawnedTargetActor = Cast<AP4TA_Trace>(Ability->GetWorld()->SpawnActorDeferred<AGameplayAbilityTargetActor>(TargetActorClass, FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn));
	if (SpawnedTargetActor)
	{
		SpawnedTargetActor->SetShowDebug(true);
		SpawnedTargetActor->TargetDataReadyDelegate.AddUObject(this, &UP4AT_Trace::OnTargetDataReadyCallback);
	}
}

void UP4AT_Trace::FinalizeTargetActor()
{
	UAbilitySystemComponent* ASC = AbilitySystemComponent.Get();
	if (ASC)
	{
		const FTransform SpawnTransform = ASC->GetAvatarActor()->GetTransform();
		SpawnedTargetActor->FinishSpawning(SpawnTransform);

		ASC->SpawnedTargetActors.Push(SpawnedTargetActor);
		SpawnedTargetActor->StartTargeting(Ability);

		// 바로 Target Actor의 ConfirmTargetingAndContinue()가 실행됨.
		SpawnedTargetActor->ConfirmTargeting();
	}
}

void UP4AT_Trace::OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& DataHandle)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnComplete.Broadcast(DataHandle);
	}

	EndTask();
}