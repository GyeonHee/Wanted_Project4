/**
* 작성 - 한승헌
* 일시 - 2025.11.13
* 
* 
**/
#pragma once
#include "CoreMinimal.h"
#include "P4ObjectiveDetails.generated.h"

UENUM(BlueprintType)
enum class EObjectiveType : uint8
{
	Location,
	Kill,
	Interact,
	Collect,
	None
};


USTRUCT(BlueprintType)
struct FP4ObjectiveDetails
{
	GENERATED_BODY()

	FP4ObjectiveDetails()
	{
		ObjectiveName = FText::FromString(TEXT("None"));
		Description = FText::FromString(TEXT("None"));
		ObjectiveType = EObjectiveType::None;
		ObjectiveID = FString();
		Quantity = 0;
	}

	FP4ObjectiveDetails(FText InObjectiveName, FText InDescription, EObjectiveType InObjectiveType, FString InObjectiveID, int32 InQuantity)
		: ObjectiveName(InObjectiveName), Description(InDescription), ObjectiveType(InObjectiveType), ObjectiveID(InObjectiveID), Quantity(InQuantity)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
	FText ObjectiveName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
	EObjectiveType ObjectiveType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
	FString ObjectiveID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
	int32 Quantity; //목표의 수량.
};
