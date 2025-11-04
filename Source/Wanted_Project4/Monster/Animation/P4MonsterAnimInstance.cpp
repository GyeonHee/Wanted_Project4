// Fill out your copyright notice in the Description page of Project Settings.


#include "P4MonsterAnimInstance.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UP4MonsterAnimInstance::UP4MonsterAnimInstance()
{
	// 이동 여부 최소값 설정
	MovingThreshold = 3.f;
}

void UP4MonsterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	// 애님 인스턴스를 갖고있는 Character 갖고 오기
	Owner = Cast<ACharacter>(GetOwningActor());

	// Character 가 있으면
	if (Owner)
	{
		// Owner 의 CharacterMovementComponent 갖고오기
		Movement = Owner->GetCharacterMovement();
	}
	
}

// 몬스터 정보를 받아와서 프레임마다 업데이트
void UP4MonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if(Movement)
	{
		// 이동하는 속도
		Velocity = Movement->Velocity;

		// 이동 속력
		MoveSpeed = Velocity.Size2D();

		// Idle 여부(1(True), 0(False))
		bIsIdle = MoveSpeed < MovingThreshold;
	}
}
