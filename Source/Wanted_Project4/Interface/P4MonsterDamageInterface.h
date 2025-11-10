// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "P4MonsterDamageInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UP4MonsterDamageInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WANTED_PROJECT4_API IP4MonsterDamageInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// 몬스터가 받는 데미지
	virtual void MonsterApplyDamage(const float DamageAmount) = 0;

	// 몬스터가 주는 데미지
	virtual void MonsterGiveDamage(AActor* TargetActor, const float DamageAmount) = 0;
};
