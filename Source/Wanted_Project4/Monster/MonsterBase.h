// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Stat/MonsterAttributeSet.h"
#include "Wanted_Project4/Interface/AnimationAttackInterface.h"
#include "MonsterBase.generated.h"

UCLASS()
class WANTED_PROJECT4_API AMonsterBase
	: public ACharacter,
	  public IAbilitySystemInterface,
	  public IAnimationAttackInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonsterBase();

	// 인터페이스로 구현하기
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	FORCEINLINE const UMonsterAttributeSet* GetAttributeSet() const { return AttributeSet; }

public:
	virtual void BeginPlay() override;

	// 애님 노티파이에서 실행할 Interface 함수 구현
	// 몬스터 공격 판정 함수
	virtual void AttackHitCheck() override;

	// ASC
	// 몬스터의 경우 일시적이므로 Character 에 붙임
protected:
	// ASC
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

	// 몬스터 스탯 AttributeSet
	UPROPERTY()
	TObjectPtr<UMonsterAttributeSet> AttributeSet;

	// 몬스터 스탯을 들고올 DataTable
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat)
	TObjectPtr<UDataTable> MonsterStatData;

	// 몬스터 이름
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat)
	FName MonsterID;

	// 선공 여부
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat)
	bool bIsAgressive;
};
