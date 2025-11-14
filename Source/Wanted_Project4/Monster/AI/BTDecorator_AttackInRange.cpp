// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/BTDecorator_AttackInRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/MonsterAIInterface.h"

UBTDecorator_AttackInRange::UBTDecorator_AttackInRange()
{
	// 이름 설정
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_AttackInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool Result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
	{
		return false;
	}

	IMonsterAIInterface* AIPawn = Cast<IMonsterAIInterface>(ControllingPawn);
	if (AIPawn == nullptr)
	{
		return false;
	}

	UObject* TargetObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target"));
	if (TargetObject == nullptr)
	{
		return false;
	}

	APawn* Target = Cast<APawn>(TargetObject);
	if (Target == nullptr)
	{
		return false;
	}

	// 공격 사거리 받기
	float AttackRange = AIPawn->GetAIAttackRange();
	
	// 타겟과의 거리
	float TargetDistance = ControllingPawn->GetDistanceTo(Target);

	// 사거리 안에 있으면 공격
	return (TargetDistance <= AttackRange);
}
