// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "P4AT_Trace.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTraceResultDelegate, const FGameplayAbilityTargetDataHandle&, TargetDataHandle);

UCLASS()
class WANTED_PROJECT4_API UP4AT_Trace : public UAbilityTask
{
	GENERATED_BODY()

public:
	UP4AT_Trace();

	static UP4AT_Trace* CreateTask(UGameplayAbility* OwningAbility, TSubclassOf<class AP4TA_Trace> TargetActorClass);

	virtual void Activate() override;
	virtual void OnDestroy(bool AbilityEnded) override;

	void SpawnAndInitializeTargetActor();
	void FinalizeTargetActor();

	FTraceResultDelegate OnComplete;

protected:
	void OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& DataHandle);

protected:
	UPROPERTY()
	TSubclassOf<class AP4TA_Trace> TargetActorClass;

	UPROPERTY()
	TObjectPtr<class AP4TA_Trace> SpawnedTargetActor;
};
