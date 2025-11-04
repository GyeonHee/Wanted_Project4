// Fill out your copyright notice in the Description page of Project Settings.


#include "P4MonsterStatComponent.h"

// Sets default values for this component's properties
UP4MonsterStatComponent::UP4MonsterStatComponent()
{
	// InitializeComponent() 호출용 설정
	bWantsInitializeComponent = true;
}


// Called when the game starts
void UP4MonsterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UP4MonsterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	// 데이터 테이블 만들어서 몬스터 스탯 불러오기

	// 현재 스탯 설정
}

float UP4MonsterStatComponent::ApplyDamage(float DamageAmount)
{
	// 데미지 처리 계산을 위해 이전 체력 저장.
	const float PrevHp = CurrentHP;

	// 데미지 값에 음수가 전달되는 것 방지
	// @Todo: Todo인가? 나중에 몬스터 체력 차는게 필요하면 지우거나 따로 힐링용 함수 만들기
	const float ActualDamage 
		= FMath::Clamp(DamageAmount, 0.0f, DamageAmount);

	// 데미지 처리
	SetHP(PrevHp - ActualDamage);

	// 체력을 모두 소진했는지 확인.
	if (CurrentHP <= KINDA_SMALL_NUMBER)
	{
		// @Todo: 나중에 사망 시 여기서 처리
	}

	return ActualDamage;
}

void UP4MonsterStatComponent::SetHP(float NewHP)
{
	// 현재 HP 를 새로운 HP 로 설정
	CurrentHP = FMath::Clamp(NewHP, 0.0f, BaseStat.MaxHP);

	// @Todo: 나중에 체력 변경 이벤트 생성 시 여기에 넣기
}



