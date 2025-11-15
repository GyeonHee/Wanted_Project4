// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "P4NPCAnimationInstance.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_PROJECT4_API UP4NPCAnimationInstance : public UAnimInstance
{
	GENERATED_BODY()

	//함수 섹션.
public:
	UP4NPCAnimationInstance();

protected:
	// 애니메이션 초기화할 때 실행되는 함수.
	virtual void NativeInitializeAnimation() override;

	// 애니메이션 업데이트할 때 프레임 마다 실행되는 함수.
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;



	//변수 섹션.
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class ACharacter> Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class UCharacterMovementComponent> Movement;

protected:
	
};
