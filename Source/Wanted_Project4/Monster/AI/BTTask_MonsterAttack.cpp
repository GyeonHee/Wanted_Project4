// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/BTTask_MonsterAttack.h"

#include "AIController.h"
#include "Interface/MonsterAIInterface.h"

UBTTask_MonsterAttack::UBTTask_MonsterAttack()
{
}

EBTNodeResult::Type UBTTask_MonsterAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	IMonsterAIInterface* AIPawn = Cast<IMonsterAIInterface>(ControllingPawn);
	if (AIPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	// 공격 종료 시 실행할 함수 전달
	AIPawn->SetAIAttackDelegate(
		FAIMonsterAttackFinished::CreateLambda(
			[&]()
			{
				// 공격이 끝난 후 태스크 실행 결과 설정
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}
		)
	);

	// Pawn 에 공격 요청
	AIPawn->AttackByAI();

	// 공격 요청 후 결과는 모르므로 진행중
	// 위에서 지정한 델리게이트가 호출되야 완료
	return EBTNodeResult::InProgress;;
}
