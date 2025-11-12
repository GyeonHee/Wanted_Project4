// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/P4BossMonsterBase.h"

// Sets default values
AP4BossMonsterBase::AP4BossMonsterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	
}

// Called when the game starts or when spawned
void AP4BossMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AP4BossMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AP4BossMonsterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AP4BossMonsterBase::SetupAttackDelegate()
{
}

void AP4BossMonsterBase::ExecuteAttackSection(const FName& SectionName)
{
	// 섹션 이름을 Index로 변경
	int32 Index = AttackSectionNames.IndexOfByKey(SectionName);
	if (AttackDelegates.IsValidIndex(Index) && AttackDelegates[Index].IsBound())
	{
		// 해당 인덱스의 함수 실행
		AttackDelegates[Index].Execute();
	}

	// 함수 없으면 로그 띄움
	else
	{
		UE_LOG(LogTemp, Log, TEXT("%s 에 해당하는 함수가 없습니다."), *SectionName.ToString());
	}
}

