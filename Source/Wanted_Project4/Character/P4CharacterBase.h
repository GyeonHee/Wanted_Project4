// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
//#include "Interface/AnimationAttackInterface.h"
#include "Interface/P4CharacterWidgetInterface.h"
#include "P4CharacterBase.generated.h"

UCLASS()
class WANTED_PROJECT4_API AP4CharacterBase : 
	public ACharacter, public IAbilitySystemInterface,
	public IP4CharacterWidgetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AP4CharacterBase();

	// GAS 접근용
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// AttributeSet 접근용
	class UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	// todo: 플레이어에 직접 둘지 아니면 플레이어가 오버라이드해야할지 모르겠음.
	//void SetupGASInputComponent();

public:
	FORCEINLINE virtual class UAnimMontage* GetDefaultAttackMontage() const { return DefaultAttackMontage; }
	FORCEINLINE virtual class UAnimMontage* GetJumpMontage() const { return JumpMontage; }
	//FORCEINLINE class UABComboActionData* GetComboActionData() const { return ComboActionData; }
	FORCEINLINE class UAnimMontage* GetDeadMontage() const { return DeadMontage; }


protected:
	virtual void PostInitializeComponents() override;

protected:
	// IABAnimationAttackInterface 함수 구현.
	// 애님 노티파이 기반으로 충돌 판정하는 목적으로 사용.
	//virtual void AttackHitCheck() override;

protected:
	// AbilitySystem
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<class UAbilitySystemComponent> ASC;

	// AttributeSet
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<class UAttributeSet> AttributeSet;

protected:
	//virtual void SetCharacterControlData(const class UABCharacterControlData* CharacterControlData);

	//UPROPERTY(EditAnywhere, Category = CharacterControl, Meta = (AllowPrivateAccess = "true"))
	//TMap<ECharacterControlType, class UABCharacterControlData*> CharacterControlManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> DefaultAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> JumpMontage;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	//TObjectPtr<class UABComboActionData> ComboActionData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DeadMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USkeletalMeshComponent> Weapon;


	//virtual void BeginPlay() override;
};
