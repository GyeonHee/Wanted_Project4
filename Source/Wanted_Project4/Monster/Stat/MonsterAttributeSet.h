// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MonsterAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_PROJECT4_API UMonsterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()


public:
	UMonsterAttributeSet();

	// PROPERTY_GETTER : GameplayEffect 에서 쓸 Attribute 핸들 생성
	// GETTER : FGameplayAttributeData 안의 값을 가져옴
	// SETTER : FGameplayAttributeData 안의 값을 수정
	// INITTER : 기본 값 설정
	ATTRIBUTE_ACCESSORS_BASIC(UMonsterAttributeSet, MaxHP);
	ATTRIBUTE_ACCESSORS_BASIC(UMonsterAttributeSet, DetectRange);
	ATTRIBUTE_ACCESSORS_BASIC(UMonsterAttributeSet, ChaseRange);
	ATTRIBUTE_ACCESSORS_BASIC(UMonsterAttributeSet, MovementSpeed);
	ATTRIBUTE_ACCESSORS_BASIC(UMonsterAttributeSet, ChaseSpeed);
	ATTRIBUTE_ACCESSORS_BASIC(UMonsterAttributeSet, TurnSpeed);
	ATTRIBUTE_ACCESSORS_BASIC(UMonsterAttributeSet, Attack);
	ATTRIBUTE_ACCESSORS_BASIC(UMonsterAttributeSet, AttackSpeed);
	
protected:
	// 스탯=======================================================
	// 최대 체력
	UPROPERTY(BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxHP;

	// 범위=======================================================
	// 탐지 범위
	UPROPERTY(BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData DetectRange;

	// 추적 범위
	UPROPERTY(BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData ChaseRange;

	// 속도=======================================================
	// 기본 속도 : Idle 에서 주변 돌아다니는 속도
	UPROPERTY(BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MovementSpeed;
	
	// 추적 속도 : Player 를 Chase 할 때 속도
	UPROPERTY(BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData ChaseSpeed;
	
	// 회전 속도 : 공격 시 회전하는 속도
	UPROPERTY(BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData TurnSpeed;

	// 공격=======================================================
	// 공격력
	UPROPERTY(BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Attack;
	
	// 공격 속도
	UPROPERTY(BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData AttackSpeed;
};
