// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interface/AnimationAttackInterface.h"
#include "P4CharacterBase.generated.h"

UCLASS()
class WANTED_PROJECT4_API AP4CharacterBase : 
	public ACharacter, public IAbilitySystemInterface, public IAnimationAttackInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AP4CharacterBase();

	// 컴포넌트 초기화가 끝나면 호출되는 이벤트 함수.
	virtual void PostInitializeComponents() override;

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// IABAnimationAttackInterface 함수 구현.
	// 애님 노티파이 기반으로 충돌 판정하는 목적으로 사용.
	virtual void AttackHitCheck() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

protected:
	
	UPROPERTY(VisibleAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

};
