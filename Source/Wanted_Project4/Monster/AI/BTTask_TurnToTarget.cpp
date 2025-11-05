// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/BTTask_TurnToTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/MonsterAIInterface.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("TurnToTarget");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	APawn* TargetPawn
		= Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (TargetPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	// 회전속도 가져오기
	float TurnSpeed = AIPawn->GetAITurnSpeed();

	// 몬스터가 바라봐야 하는 방향
	FVector LookVector = TargetPawn->GetActorLocation() - ControllingPawn->GetActorLocation();
	// 위 아래 회전 막기
	LookVector.Z = 0.f;
	LookVector.Normalize();
	
	// 회전 값
	FRotator TargetRotator = FRotationMatrix::MakeFromX(LookVector).Rotator();

	// 몬스터의 Rotator 에서 Target 의 Rotator 로 부드럽게 전환 (RInterpTo)
	FRotator FinalRotator = FMath::RInterpTo(
		ControllingPawn->GetActorRotation(),
		TargetRotator,
		ControllingPawn->GetWorld()->GetDeltaSeconds(),
		TurnSpeed
	);

	// 회전값 설정
	ControllingPawn->SetActorRotation(FinalRotator);

	return EBTNodeResult::Succeeded;
}
