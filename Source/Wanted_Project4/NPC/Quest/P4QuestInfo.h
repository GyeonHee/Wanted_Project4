/**
* 작성 - 한승헌
* 일시 - 2025.11.13
* 퀘스트의 기본 정볼르 적어넣는 구조체입니다.
* 
* 
**/
#pragma	once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "P4StageDetails.h"
#include "P4QuestInfo.generated.h"

UENUM(BlueprintType)
enum class EQuestType : uint8
{
	MainQuest,
	SideQuest,
	None
};

USTRUCT(BlueprintType)
struct FP4QuestInfo : public FTableRowBase
{
	GENERATED_BODY()
	FP4QuestInfo()
		:QuestCode(0)
	{
		QuestName = FText::FromString(TEXT("NoneName"));
		LogDescription = FText::FromString(TEXT("NoneLog"));
		TrackingDescription = FText::FromString(TEXT("NoneLog"));
	}

	FP4QuestInfo(int32 InQuestCode, FText InQuestName, FText InLogDescription, FText InTrackingDescription,EQuestType InQuestType)
		: QuestCode(InQuestCode), QuestName(InQuestName), LogDescription(InLogDescription), TrackingDescription(InTrackingDescription), QuestType(InQuestType)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
	int32 QuestCode; //퀘스트 코드.

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
	FText QuestName;//퀘스트 이름.

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
	FText LogDescription; //퀘스트 UI창에 나타날 설명.

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
	FText TrackingDescription; //HUD에 나타날 작은 설명문.

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
	EQuestType QuestType = EQuestType::None; //퀘스트 타입.

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
	TArray<FP4StageDetails> Stages;
};