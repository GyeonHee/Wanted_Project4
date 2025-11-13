/**
* 작성 - 한승헌
* 일시 = 2025.11.13
* 
* 
* 
**/
#pragma once
#include "CoreMinimal.h"
#include "P4ObjectiveDetails.h"
#include "P4StageDetails.generated.h"

//struct FP4ObjectiveDetails;

USTRUCT(BlueprintType)
struct FP4StageDetails
{
	GENERATED_BODY()

	FP4StageDetails()
		:XpReward(0)
	{
		StageName = FText::FromString(TEXT("None"));
		Description = FText::FromString(TEXT("None"));
		//Objectives = FText::FromString(TEXT("None"));
	}

	FP4StageDetails(FText InStageName, FText InDescription, TArray<FP4ObjectiveDetails> InObjectives, int32 InXpReward)
		: StageName(InStageName), Description(InDescription), Objectives(InObjectives), XpReward(InXpReward)
	{

	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
	FText StageName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
	TArray<FP4ObjectiveDetails> Objectives;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
	int32 XpReward; //나중에 XP추가하면 연동 일단 지금은 더미값.

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Quest)
	//TMap<FName, AActor> ItemRewards;



};