// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/P4QuestInformationWidget.h"
#include "Game/P4GameInstance.h"
#include "NPC/Quest/P4QuestManager.h"
#include "Components/TextBlock.h"

void UP4QuestInformationWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	UWorld* world = GetWorld();
	if (world != nullptr)
	{
		UP4GameInstance* GI = world->GetGameInstance<UP4GameInstance>(); //싱글톤 게임 인스턴스 받아오기.

		if (GI != nullptr)
		{
			QuestManager = GI->QuestManager;
		}
	}

	RefreshQuestUI();

	if (QuestManager != nullptr)
	{
		QuestManager->OnQuestStarted.AddUObject(this, &UP4QuestInformationWidget::HandleQuestStarted);
		QuestManager->OnQuestCleared.AddUObject(this, &UP4QuestInformationWidget::HandleQuestCleared);
	}

	//시작할땐 숨기기.
	SetVisibility(ESlateVisibility::Hidden);
}

void UP4QuestInformationWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//RefreshQuestUI();
}

void UP4QuestInformationWidget::RefreshQuestUI()
{
	if (QuestName == nullptr || Stage == nullptr ||
		CurrentProgress == nullptr || ObjectiveProgress == nullptr)
	{
		return;
	}

	//if (QuestManager == nullptr || QuestManager->IsQuestActive() == false) //퀘스트 매니저가 없거나, 퀘스트가 액티브된 상태가 아니면.
	//{
	//	QuestName->SetText(FText::FromString(TEXT("진행중인 퀘스트 없음")));
	//	Stage->SetText(FText::GetEmpty());
	//	CurrentProgress->SetText(FText::FromString(TEXT("0")));
	//	ObjectiveProgress->SetText(FText::FromString(TEXT("0")));

	//	if (GetVisibility() != ESlateVisibility::Collapsed)
	//	{
	//		SetVisibility(ESlateVisibility::Collapsed);
	//	}

	//	//if (GetVisibility() != ESlateVisibility::Hidden)
	//	//{
	//	//	SetVisibility(ESlateVisibility::Hidden);
	//	//}

	//	return;
	//}

	if (GetVisibility() != ESlateVisibility::Visible)
	{
		SetVisibility(ESlateVisibility::Visible);
	}

	//현재 퀘스트하고 현재 퀘스트의 스테이지 가져오기.
	const FP4QuestInfo* Quest = QuestManager->GetCurrentQuest();
	const FP4StageDetails* StageInfo = QuestManager->GetCurrentStage();

	if (Quest == nullptr || StageInfo == nullptr)
	{
		return;
	}

	QuestName->SetText(Quest->QuestName);
	Stage->SetText(StageInfo->StageName);

	if (StageInfo->Objectives.Num() > 0)
	{
		const FP4ObjectiveDetails& Obj = StageInfo->Objectives[0];

		int32 Cur = QuestManager->GetObjectiveProgress(Obj.ObjectiveID);
		int32 Target = Obj.Quantity;

		CurrentProgress->SetText(FText::AsNumber(Cur));
		ObjectiveProgress->SetText(FText::AsNumber(Target));
	}

	else
	{
		CurrentProgress->SetText(FText::FromString(TEXT("0")));
		ObjectiveProgress->SetText(FText::FromString(TEXT("0")));
	}
}

void UP4QuestInformationWidget::HandleQuestStarted()
{
	// 퀘스트 시작되면 보이게
	SetVisibility(ESlateVisibility::Visible);

	RefreshQuestUI();
}

void UP4QuestInformationWidget::HandleQuestCleared()
{
	// 퀘스트 끝나면 숨기기
	SetVisibility(ESlateVisibility::Hidden);

	//RefreshQuestUI();
}
