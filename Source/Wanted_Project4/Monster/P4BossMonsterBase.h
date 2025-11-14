// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Stat/P4MonsterAttributeSet.h"
#include "P4BossMonsterBase.generated.h"

/*
 * 클래스 명 : P4BossMonsterBase
 * 기능 : 보스 몬스터의 기본 기능을 담당
 * ---------------------------------------
 * 스탯, 애니메이션, AI
 * 스탯 : AttributeSet, Gameplay Effect 를 사용해서 관리 및 조정
 * AI : Tick 에서 일정 시간마다 패턴 발동 확률 계산 -> 발동 조건 충족 시 StartPattern (이동중단)
 * 패턴 : Gameplay Ability 로 각 보스 몬스터 클래스에서 생성
 */


// 몬스터 공격 시 각 공격을 실행할 델리게이트
DECLARE_DELEGATE(FBossMonsterAttackDelegate);

UCLASS()
class WANTED_PROJECT4_API AP4BossMonsterBase
	: public ACharacter,
	  public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AP4BossMonsterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return ASC;
	}

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// ASC 섹션
protected:
	// ASC
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

	// 보스몬스터 스탯 AttributeSet
	UPROPERTY()
	TObjectPtr<UP4MonsterAttributeSet> AttributeSet;

	// 몬스터 이름
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Stat)
	FName MonsterID;


	// 애니메이션 섹션
protected:
	// 공격 애님 몽타주
	UPROPERTY(EditAnywhere, Category = MonsterControl, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> AttackActionMontage;

	// 몬스터 피격 몽타주
	UPROPERTY(EditAnywhere, Category = MonsterControl, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DamagedMontage;

	// 몬스터 사망 몽타주
	UPROPERTY(EditAnywhere, Category = MonsterControl, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DeadMontage;


	// 몬스터 공격 관리 섹션
protected:
	// 공격 델리게이트를 배열로 저장
	TArray<FBossMonsterAttackDelegate> AttackDelegates;

	// 공격 몽타주 섹션 이름 배열
	// 실제 섹션 배치와 이름이 동일해야 함
	UPROPERTY(EditAnywhere, Category = Attack)
	TArray<FName> AttackSectionNames;

	// 공격 델리게이트 배열을 설정 (자식이 오버라이드)
	virtual void SetupAttackDelegate();

public:
	void ExecuteAttackSection(const FName& SectionName);
	
	
};
