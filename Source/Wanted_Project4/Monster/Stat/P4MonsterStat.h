// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "P4MonsterStat.generated.h"

/*
* MaxHP, DetectRange, ChaseRange, MovementSpeed, ChaseSpeed, TurnSpeed, Attack, AttackSpeed, bIsAggressive
*/

USTRUCT(BlueprintType)
struct FP4MonsterStat : public FTableRowBase
{
	GENERATED_BODY()

	FP4MonsterStat()
		: MaxHP(0.f),
		  DetectRange(0.f), ChaseRange(0.f),
		  MovementSpeed(0.f), ChaseSpeed(0.f), TurnSpeed(0.f),
		  Attack(0.f), AttackSpeed(0.f), bIsAggressive(false)
	{
	}
	
	// 스탯=======================================================
	// 최대 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MaxHP;

	// 범위=======================================================
	// 탐지 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float DetectRange;

	// 추적 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float ChaseRange;

	// 공격 범위
	// : 공격 범위는 기술들마다 다르므로 기술에서 처리해주는게 맞는 것 같음

	// 속도=======================================================
	// 기본 속도
	// : Idle 에서 주변 돌아다니는 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MovementSpeed;

	// 추적 속도
	// : Player 를 Chase 할 때 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float ChaseSpeed;

	// 회전 속도
	// : 공격 시 회전하는 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float TurnSpeed;

	// 공격=======================================================
	// 공격력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float Attack;

	// 공격 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackSpeed;

	// 선공 여부
	// True : 몬스터 범위 내에 플레이어가 있으면 자동 공격
	// False : 플레이어가 먼저 공격하기 전엔 공격 X
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	bool bIsAggressive;
};
