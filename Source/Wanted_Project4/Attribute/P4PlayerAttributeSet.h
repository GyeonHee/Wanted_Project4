// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "P4PlayerAttributeSet.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);

UCLASS()
class WANTED_PROJECT4_API UP4PlayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UP4PlayerAttributeSet();

	ATTRIBUTE_ACCESSORS_BASIC(UP4PlayerAttributeSet, AttackRange);
	ATTRIBUTE_ACCESSORS_BASIC(UP4PlayerAttributeSet, MaxAttackRange);
	ATTRIBUTE_ACCESSORS_BASIC(UP4PlayerAttributeSet, AttackRadius);
	ATTRIBUTE_ACCESSORS_BASIC(UP4PlayerAttributeSet, MaxAttackRadius);
	ATTRIBUTE_ACCESSORS_BASIC(UP4PlayerAttributeSet, AttackRate);
	ATTRIBUTE_ACCESSORS_BASIC(UP4PlayerAttributeSet, MaxAttackRate);
	ATTRIBUTE_ACCESSORS_BASIC(UP4PlayerAttributeSet, Health);
	ATTRIBUTE_ACCESSORS_BASIC(UP4PlayerAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS_BASIC(UP4PlayerAttributeSet, Damage);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	//virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	// const를 무시해주기 위함. 죽음 델리게이트
	mutable FOnHpZeroDelegate OnHpZero;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRange;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackRange;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRadius;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackRadius;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRate;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackRate;

	UPROPERTY(BlueprintReadOnly, Category = "Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Damage;

	bool bOutOfHealth = false;

	friend class UP4GE_AttackDamage;
};
