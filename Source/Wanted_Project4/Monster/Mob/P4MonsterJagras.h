// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../P4MonsterBase.h"
#include "P4MonsterJagras.generated.h"
/**
 * 
 */

UCLASS()
class WANTED_PROJECT4_API AP4MonsterJagras : public AP4MonsterBase
{
	GENERATED_BODY()

public:
	AP4MonsterJagras();

protected:
	virtual void AttackByAI() override;
	virtual void AttackHitCheck() override;

	virtual void SetupAttackDelegate() override;

	// 몬스터 스킬별 공격 판정 함수
protected:
	void MeleeAttack();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBoxComponent> BoxCollision;
	
};
