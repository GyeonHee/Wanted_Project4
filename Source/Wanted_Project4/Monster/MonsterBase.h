// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Stat/MonsterAttributeSet.h"
#include "MonsterBase.generated.h"

UCLASS()
class WANTED_PROJECT4_API AMonsterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonsterBase();

	// 인터페이스로 구현하기
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	const UMonsterAttributeSet* GetAttributeSet() const { return AttributeSet; }

public:
	virtual void BeginPlay() override;
	
protected:
	// ASC
	// 몬스터의 경우 일시적이므로 Character 에 붙임
protected:
	// ASC
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

	// 몬스터 스탯 ATtributeSet
	UPROPERTY()
	TObjectPtr<UMonsterAttributeSet> AttributeSet;
};
