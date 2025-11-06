// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interface/AnimationAttackInterface.h"
#include "P4CharacterBase.generated.h"

UCLASS()
class WANTED_PROJECT4_API AP4CharacterBase : 
	public ACharacter, public IAbilitySystemInterface, public IAnimationAttackInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AP4CharacterBase();

	// GAS 접근용
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// AttributeSet 접근용
	class UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	virtual void PostInitializeComponents() override;

protected:
	// IABAnimationAttackInterface 함수 구현.
	// 애님 노티파이 기반으로 충돌 판정하는 목적으로 사용.
	virtual void AttackHitCheck() override;

protected:
	// AbilitySystem
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<class UAbilitySystemComponent> ASC;

	// AttributeSet
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<class UAttributeSet> AttributeSet;
};
