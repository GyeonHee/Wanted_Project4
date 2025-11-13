// Fill out your copyright notice in the Description page of Project Settings.


#include "P4QuestManager.h"

UP4QuestManager::UP4QuestManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> QuestTableRef(TEXT("/Game/Quest/QuestData.QuestData"));

	if (QuestTableRef.Succeeded())
	{
		QuestTable = QuestTableRef.Object;
	}
}

const FP4QuestInfo* UP4QuestManager::GetQuest(int32 QuestCode) const
{
	return nullptr;
}


void UP4QuestManager::StartQuest(int32 QuestCode)
{
}

void UP4QuestManager::UpdateObjective(const FString& ObjectiveID)
{
}
