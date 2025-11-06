// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interface/MonsterAIInterface.h"
#include "Stat/P4MonsterAttributeSet.h"
#include "Wanted_Project4/Interface/AnimationAttackInterface.h"
#include "P4MonsterBase.generated.h"


UCLASS()
class WANTED_PROJECT4_API AP4MonsterBase
	: public ACharacter,
	  public IAbilitySystemInterface,
	  public IAnimationAttackInterface,
	  public IMonsterAIInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AP4MonsterBase();

	// 인터페이스로 구현하기
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	FORCEINLINE const UP4MonsterAttributeSet* GetAttributeSet() const { return AttributeSet; }

public:
	virtual void BeginPlay() override;

	// 애님 노티파이에서 실행할 Interface 함수 구현
	// 몬스터 공격 판정 함수
	virtual void AttackHitCheck() override;

public:
	// 공격 받았을 경우 처리 함수
	UFUNCTION(BlueprintCallable, Category = Monster)
	void MonsterApplyDamage(const float DamageAmount);

	// Monster AI Interface 구현
public:
	// AttributeSet 에 있음
	FORCEINLINE virtual float GetAIDetectRange() override { return AttributeSet->GetDetectRange(); }
	FORCEINLINE virtual float GetAIChaseRange() override { return AttributeSet->GetChaseRange(); }
	FORCEINLINE virtual float GetAITurnSpeed() override { return AttributeSet->GetTurnSpeed(); }

	// @Todo: AttributeSet 에 없는 애들을 일단 어떻게 할 것인가
	// AttributeSet 에 없음
	FORCEINLINE virtual float GetAIAttackRange() override { return 150.f; }
	FORCEINLINE virtual float GetAIPatrolRadius() override { return 500.f; }

	// 공격 요청 함수
	virtual void AttackByAI() override;

	// 공격 종료 시점 델리게이트 호출 함수 (종료 시점임을 알림)
	virtual void SetAIAttackDelegate(const FAIMonsterAttackFinished& InOnAttackFinished) override;

	// 공격 몽타주가 끝나면 알려주는 함수
	virtual void NotifyActionEnd();
	
	//SetAIAttackDelegate 에서 전달된 델리게이트를 저장할 변수
	FAIMonsterAttackFinished OnAttackFinished;

	// 입력받은 섹션 네임의 공격 몽타주를 실행할 함수
	virtual void AttackActionBegin(FName& InAttackMontageSectionName, const float AttackSpeed);
	void AttackActionEnd(UAnimMontage* TargetMontage, bool Interrupted);
	
	// ASC
	// 몬스터의 경우 일시적이므로 Character 에 붙임
protected:
	// ASC
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

	// 몬스터 스탯 AttributeSet
	UPROPERTY()
	TObjectPtr<UP4MonsterAttributeSet> AttributeSet;

	// 몬스터 스탯을 들고올 DataTable
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat)
	TObjectPtr<UDataTable> MonsterStatData;

	// 몬스터 이름
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat)
	FName MonsterID;

	// 선공 여부
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat)
	bool bIsAgressive;

	// 애니메이션 관련
protected:
	// 몬스터 공격 애님 몽타주
	UPROPERTY(EditAnywhere, Category = MonsterControl, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> AttackActionMontage;

	// 몬스터 사망 몽타주
	UPROPERTY(EditAnywhere, Category = MonsterControl, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DeadMontage;
};
