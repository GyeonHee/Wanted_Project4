// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/BTTask_FindPatrolPos.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/MonsterAIInterface.h"

EBTNodeResult::Type UBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	// AIController 를 소유하는 Pawn 갖고오기
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	// 랜덤 패트롤 위치 선택을 위한 내비시스템 갖고오기
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (NavSys == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	// MonsterAIInterface 로 형변환
	IMonsterAIInterface* AIPawn = Cast<IMonsterAIInterface>(ControllingPawn);
	if (AIPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	// 기존 HomePos 받아오기
	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("HomePos"));
	
	FNavLocation NextPatrolPos;

	// AIPawn 에서 PatrolRadius 받아오기
	float PatrolRadius = AIPawn->GetAIPatrolRadius();

	// Origin 기준 PatrolRadius 반경에서 이동 가능한 랜덤 위치를 NextPatrolPos로
	bool SelectPositionResult =
		NavSys->GetRandomPointInNavigableRadius(Origin, PatrolRadius, NextPatrolPos);

	if (SelectPositionResult)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolPos"), NextPatrolPos.Location);

		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
