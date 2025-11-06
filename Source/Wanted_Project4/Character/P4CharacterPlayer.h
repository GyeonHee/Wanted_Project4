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
	// GAS
	UPROPERTY(EditAnywhere, Category = GAS)
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;

	UPROPERTY(EditAnywhere, Category = GAS)
	TMap<int32, TSubclassOf<class UGameplayAbility>> StartInputAbilities;

	//UPROPERTY(EditAnywhere, Category = Weapon)
	//TObjectPtr<class USkeletalMesh> WeaponMesh;
};
