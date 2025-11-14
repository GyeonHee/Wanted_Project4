// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "P4DamageableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UP4DamageableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class WANTED_PROJECT4_API IP4DamageableInterface
{
	GENERATED_BODY()

public:
	// 받는 데미지 (피격)
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
	virtual void ApplyDamage(const float DamageAmount  /*, AActor* DamageCauser*/) = 0;

	// 주는 데미지 (공격)
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
	virtual void GiveDamage(AActor* TargetActor, const float DamageAmount) = 0;
};
