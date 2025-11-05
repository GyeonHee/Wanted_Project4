// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/P4MonsterAIController.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AP4MonsterAIController::AP4MonsterAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(
		TEXT("/Game/Monster/AI/BB_Monster.BB_Monster")
	);
	if (BBAssetRef.Succeeded())
	{
		BBAsset = BBAssetRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(
		TEXT("/Game/Monster/AI/BT_Monster.BT_Monster")
	);
	if (BTAssetRef.Succeeded())
	{
		BTAsset = BTAssetRef.Object;
	}
}

void AP4MonsterAIController::RunAI()
{
	// 블랙보드 컴포넌트 받기
	UBlackboardComponent* BBComp = Blackboard.Get();

	// 블랙보드 사용 설정
	if (UseBlackboard(BBAsset, BBComp))
	{
		// 블랙보드 키 값 초기화
		FVector HomePos = GetPawn()->GetActorLocation();
		Blackboard->SetValueAsVector(TEXT("HomePos"), HomePos);

		// BT 실행
		bool Result = RunBehaviorTree(BTAsset);

		// 어썰트
		ensureAlways(Result);
	}
}

void AP4MonsterAIController::StopAI()
{
	// 실행중인 BT 컴포넌트 받기
	UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComp)
	{
		BTComp->StopTree();
	}
}

void AP4MonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// 컨트롤러가 Pawn 에 빙의하면 AI 실행
	RunAI();
}
