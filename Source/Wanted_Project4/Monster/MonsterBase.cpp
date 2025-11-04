// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBase.h"

#include "AbilitySystemComponent.h"
#include "Stat/MonsterAttributeSet.h"
#include "Stat/MonsterStatComponent.h"

// Sets default values
AMonsterBase::AMonsterBase()
{
	// ASC
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UMonsterAttributeSet>(TEXT("AttributeSet"));
	ASC->AddAttributeSetSubobject<UMonsterAttributeSet>(AttributeSet);

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

void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	if (ASC)
	{
		ASC->InitAbilityActorInfo(this, this);
		// @Todo: 데이터 테이블에서 초기 스탯을 불러와서 AttributeSet 초기화
		if (AttributeSet)
		{
			// 데이터 테이블에서 이름으로 Row 값 받아와서 값 설정하기
			if (const FMonsterStat* Row = MonsterStatData->FindRow<FMonsterStat>(MonsterID, TEXT("Monster Data Init")))
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

UAbilitySystemComponent* AMonsterBase::GetAbilitySystemComponent() const
{
	return ASC;
}
