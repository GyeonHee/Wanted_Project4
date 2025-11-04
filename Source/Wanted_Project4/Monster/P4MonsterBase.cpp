// Fill out your copyright notice in the Description page of Project Settings.


#include "P4MonsterBase.h"

#include "AbilitySystemComponent.h"
#include "Stat/P4MonsterAttributeSet.h"
#include "Stat/P4MonsterStatComponent.h"

// Sets default values
AP4MonsterBase::AP4MonsterBase()
{
	// ASC
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UP4MonsterAttributeSet>(TEXT("AttributeSet"));
	ASC->AddAttributeSetSubobject<UP4MonsterAttributeSet>(AttributeSet);

	// Monster Stat Data Table
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableRef(
		TEXT("/Game/Monster/Data/MonsterData.MonsterData")
	);
	if (DataTableRef.Succeeded())
	{
		MonsterStatData = DataTableRef.Object;
	}

	// @Todo: 테스트용 임시
	MonsterID = FName("Jagras");
}

void AP4MonsterBase::BeginPlay()
{
	Super::BeginPlay();
	if (ASC)
	{
		ASC->InitAbilityActorInfo(this, this);
		// 데이터 테이블에서 초기 스탯을 불러와서 AttributeSet 초기화
		if (AttributeSet)
		{
			// 데이터 테이블에서 이름으로 Row 값 받아와서 값 설정하기
			if (const FP4MonsterStat* Row = MonsterStatData->FindRow<FP4MonsterStat>(MonsterID, TEXT("Monster Data Init")))
			{
				// AttributeSet 세팅
				AttributeSet->SetMaxHP(Row->MaxHP);
				AttributeSet->SetDetectRange(Row->DetectRange);
				AttributeSet->SetChaseRange(Row->ChaseRange);
				AttributeSet->SetMovementSpeed(Row->MovementSpeed);
				AttributeSet->SetChaseSpeed(Row->ChaseSpeed);
				AttributeSet->SetTurnSpeed(Row->TurnSpeed);
				AttributeSet->SetAttack(Row->Attack);
				AttributeSet->SetAttackSpeed(Row->AttackSpeed);

				// MonsterBase 의 선공 여부 세팅
				bIsAgressive = Row->bIsAggressive;

				UE_LOG(LogTemp, Log, TEXT("MaxHP: %f"), AttributeSet->GetMaxHP());
				UE_LOG(LogTemp, Log, TEXT("DetectRange: %f"), AttributeSet->GetDetectRange());
				UE_LOG(LogTemp, Log, TEXT("ChaseRange: %f"), AttributeSet->GetChaseRange());
				UE_LOG(LogTemp, Log, TEXT("MovementSpeed: %f"), AttributeSet->GetMovementSpeed());
				UE_LOG(LogTemp, Log, TEXT("Attack: %f"), AttributeSet->GetAttack());
			}
		}
	}
}

void AP4MonsterBase::AttackHitCheck()
{
}

UAbilitySystemComponent* AP4MonsterBase::GetAbilitySystemComponent() const
{
	return ASC;
}
