// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Mob/P4BossMonsterNemielle.h"

AP4BossMonsterNemielle::AP4BossMonsterNemielle()
{
	MonsterID = FName("Nemielle");

	// Mesh 설정
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -86.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetRelativeScale3D(FVector(.8f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshRef(
		TEXT("/Game/Monster/Model/Nemielle/Nemielle.Nemielle")
		);
	if (MeshRef.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceRef(
		TEXT("/Game/Monster/Animation/ABP_Namielle.ABP_Namielle_C")
	);
	if (AnimInstanceRef.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceRef.Class);
	}

	// @Todo: 보스 몬스터 몽타주 생성자 초기화


	// AI 설정 ===============================================
	//AIControllerClass = AP4BossMonsterAIController::StaticClass();

	//AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AP4BossMonsterNemielle::SetupAttackDelegate()
{
	Super::SetupAttackDelegate();

	// @Todo: 보스 몬스터 패턴 생기면 Delegate 생성 후 넘겨주기
}



