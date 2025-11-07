// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/P4CharacterBase.h"
#include "InputActionValue.h"
#include "P4CharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_PROJECT4_API AP4CharacterPlayer : public AP4CharacterBase
{
	GENERATED_BODY()

public:
	AP4CharacterPlayer();

	// 컨트롤러가 호출하는 함수들
public:
	// 입력 제어 함수
	void GASInputPressed(int32 InputId);
	void GASInputReleased(int32 InputId);

	// 입력 처리 함수
	void HandleMove(const FInputActionValue& Value);
	void HandleLook(const FInputActionValue& Value);
	
protected:
	// components.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> Camera;

protected:
	///Script/Engine.AnimMontage'/Game/Character/Animation/AM_Rolling.AM_Rolling'
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> RollingMontage;

	///Script/Engine.AnimMontage'/Game/Character/Animation/AM_Rolling.AM_Rolling'
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> RunMontage;
public:
	// GAS
	//UPROPERTY(EditAnywhere, Category = GAS)
	//TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;

	UPROPERTY(EditAnywhere, Category = GAS)
	TMap<int32, TSubclassOf<class UGameplayAbility>> StartInputAbilities;

private:
	//UPROPERTY(EditAnywhere, Category = Weapon)
	//TObjectPtr<class USkeletalMesh> WeaponMesh;
};
