// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "P4GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_PROJECT4_API UP4GameInstance : public UGameInstance
{
	GENERATED_BODY()
	//함수 섹션.
public:
	UP4GameInstance();

	virtual void Init() override;
protected:

	//변수섹션.
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
	TObjectPtr<class UP4QuestManager> QuestManager;

protected:
};
