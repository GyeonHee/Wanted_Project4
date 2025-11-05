// Fill out your copyright notice in the Description page of Project Settings.


#include "P4MonsterBase.h"

#include "AbilitySystemComponent.h"
#include "AI/P4MonsterAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Stat/P4MonsterAttributeSet.h"
#include "Stat/P4MonsterStatComponent.h"

// Sets default values
AP4MonsterBase::AP4MonsterBase()
{
	// ASC 설정===========================================
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

	// AI 설정===========================================
	AIControllerClass = AP4MonsterAIController::StaticClass();

	// 맵에 배치 또는 생성 시 MonsterAIController 에 빙의되도록
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

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
	// @Todo: 공격 판정 구현 필요
	
}

void AP4MonsterBase::AttackByAI()
{
	// 각 몬스터 Class 에서 AttackActionBegin(FName& InAttackMontageSectionName) 으로
	// 공격 몽타주 섹션 이름 넘겨줘서 공격 실행
}

void AP4MonsterBase::SetAIAttackDelegate(const FAIMonsterAttackFinished& InOnAttackFinished)
{
	// 전달받은 델리게이트 저장
	OnAttackFinished = InOnAttackFinished;
}

void AP4MonsterBase::NotifyActionEnd()
{
	// 공격 끝날 시 전달받은 델리게이트 호출
	// 여기서는 공격 완료 상태 전달
	OnAttackFinished.ExecuteIfBound();
}

void AP4MonsterBase::AttackActionBegin(FName& InAttackMontageSectionName, const float AttackSpeed)
{
	// 공격 모션동안 이동 막기
	GetCharacterMovement()->SetMovementMode(MOVE_None);

	// 몽타주 재생을 위해 AnimInstance 갖고 오기
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		// 입력받은 섹션으로 몽타주 섹션 변경
		AnimInstance->Montage_JumpToSection(InAttackMontageSectionName, AttackActionMontage);
		
		// 몽타주 실행 
		AnimInstance->Montage_Play(AttackActionMontage, AttackSpeed);

		// 몽타주 재생이 끝날 때 실행될 함수 바인딩
		FOnMontageEnded OnMontageEnded;
		OnMontageEnded.BindUObject(this, &AP4MonsterBase::AttackActionEnd);

		// 몽타주 재생 종료 시 바인딩한 델리게이트 실행
		AnimInstance->Montage_SetEndDelegate(OnMontageEnded, AttackActionMontage);

		
	}
}

void AP4MonsterBase::AttackActionEnd(UAnimMontage* TargetMontage, bool Interrupted)
{
	// 무브먼트 모드 복구
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);

	// 공격이 끝났음을 알림
	NotifyActionEnd();
}

UAbilitySystemComponent* AP4MonsterBase::GetAbilitySystemComponent() const
{
	return ASC;
}
