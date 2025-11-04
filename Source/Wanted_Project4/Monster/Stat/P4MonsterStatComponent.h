// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "P4MonsterStat.h"
#include "Components/ActorComponent.h"
#include "P4MonsterStatComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WANTED_PROJECT4_API UP4MonsterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UP4MonsterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// 컴포넌트 초기화용
	virtual void InitializeComponent() override;

public:
	// Getter 함수
	FORCEINLINE const FP4MonsterStat& GetBaseStat() const { return BaseStat; }
	FORCEINLINE float GetCurrentHP() const { return CurrentHP; }

	// 공격 받을 시 데미지 적용 함수
	float ApplyDamage(float DamageAmount);
	
protected:
	// 체력 변경 시 실행 함수
	void SetHP(float NewHP);
	


	// 스탯 영역
protected:
	UPROPERTY(Transient, VisibleAnywhere, Category = Stat, meta = (AllowPrivateAccess = "true"))
	float CurrentHP;

	// 몬스터 기본 스탯
	UPROPERTY(Transient, VisibleAnywhere, Category = Stat, meta = (AllowPrivateAccess = "true"))
	FP4MonsterStat BaseStat;
};
