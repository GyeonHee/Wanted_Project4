// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_PROJECT4_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UMonsterAnimInstance();

protected:
	// 애니메이션 초기화할 때 실행되는 함수.
	virtual void NativeInitializeAnimation() override;

	// 애니메이션 업데이트할 때 프레임 마다 실행되는 함수.
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	// 블루프린트용 변수
protected:
	// 참조 변수.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	TObjectPtr<class ACharacter> Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	TObjectPtr<class UCharacterMovementComponent> Movement;

	// 이동하는 속도(무브먼트 컴포넌트에서 읽기).
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	FVector Velocity;

	// 이동 속력
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	float MoveSpeed;

	// 이동 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	uint8 bIsIdle : 1;

	// 이동 여부를 판단할 때 사용할 최소값
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	float MovingThreshold;
};
