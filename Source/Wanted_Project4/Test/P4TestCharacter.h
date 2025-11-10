// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayAbilities/Public/AbilitySystemInterface.h"
#include "P4TestCharacter.generated.h"

UCLASS()
class WANTED_PROJECT4_API AP4TestCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AP4TestCharacter();

	// IAbilitySystemInterface 구현
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComp; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// 인벤토리 컴포넌트 (컨트롤러에서 접근)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TObjectPtr<class UP4InventoryComponent> InventoryComp;

	// 어빌리티 시스템 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability")
	TObjectPtr<class UAbilitySystemComponent> AbilitySystemComp;

};
