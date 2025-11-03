// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBase.h"

#include "AbilitySystemComponent.h"
#include "Stat/MonsterAttributeSet.h"
#include "Stat/MonsterStatComponent.h"

// Sets default values
AMonsterBase::AMonsterBase()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UMonsterAttributeSet>(TEXT("AttributeSet"));
	
}

void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	// @Todo: ASC 초기화

	// 데이터 테이블에서 초기 스탯을 불러와서 AttributeSet 초기화
}

UAbilitySystemComponent* AMonsterBase::GetAbilitySystemComponent() const
{
	// @Todo: 오류 방지용 임시
	return ASC;
}

