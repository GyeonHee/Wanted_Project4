// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/P4MonsterPatternComponent.h"

// Sets default values for this component's properties
UP4MonsterPatternComponent::UP4MonsterPatternComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// 현재 패턴 풀을 입력받은 패턴 데이터 배열로 초기화
void UP4MonsterPatternComponent::InitializePatterns(const TArray<FPatternData>& InPatterns)
{
	PatternPool = InPatterns;	
}

// 가중치 계산을 통해 패턴 선택, 실행함수 호출
void UP4MonsterPatternComponent::TryExecutePattern(AActor* Target)
{
	// 후보 필터링
		// IsPatternAvailable 함수 사용

	// 가중치 계산
		// 타겟과의 거리

		// 최근 사용 빈도

		// 음수 -> 0으로

	// 전체 가중치의 총합이 0
		// 사용 가능한 패턴 중 랜덤 1개 실행

	// 가중치를 이용해서 패턴 실행
	
}

bool UP4MonsterPatternComponent::IsPatternAvailable(const FPatternData& Pattern, float Distance) const
{
	// 쿨타임 필터링

	// 사거리 필터링
	
	
	return true;
}

void UP4MonsterPatternComponent::ExecutePattern(const FPatternData& Pattern)
{
	// AbilityTag 를 통해 패턴 Ability 찾기

	// 해당 패턴 쿨타임 기록
}

