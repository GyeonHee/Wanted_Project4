// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "P4PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_PROJECT4_API AP4PlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AP4PlayerState();

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY()
	TObjectPtr<class UP4PlayerAttributeSet> AttributeSet;

	//UPROPERTY()
	//TObjectPtr<class UP4SkillAttributeSet> SkillAttributeSet;
	
};
