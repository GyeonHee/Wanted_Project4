// Fill out your copyright notice in the Description page of Project Settings.
/**
* 작성 - 한승헌
* 일시 = 2025.11.13
*
*
*
**/
#pragma once

#include "CoreMinimal.h"
#include "P4QuestInfo.h"
#include "UObject/NoExportTypes.h"
#include "P4QuestManager.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_PROJECT4_API UP4QuestManager : public UObject
{
	GENERATED_BODY()
	
	//함수 섹션
public:
	UP4QuestManager();

	const FP4QuestInfo* GetQuest(int32 QuestCode) const;

	void StartQuest(int32 QuestCode);
	void UpdateObjective(const FString& ObjectiveID);
protected:

	//변수 섹션
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Quest)
	UDataTable* QuestTable;



protected:

};
