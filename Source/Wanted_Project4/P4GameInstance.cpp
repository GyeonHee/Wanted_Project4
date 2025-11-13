// Fill out your copyright notice in the Description page of Project Settings.


#include "P4GameInstance.h"
#include "NPC/Quest/P4QuestManager.h"

UP4GameInstance::UP4GameInstance()
{
}

void UP4GameInstance::Init()
{
	Super::Init();

	QuestManager = NewObject<UP4QuestManager>(this);
	QuestManager->AddToRoot(); //가비지 컬렉터가 납치 못하게 방지.
}
