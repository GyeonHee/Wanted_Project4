// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/P4CustomWidget.h"
#include "P4QuestWidget.generated.h"

/**
 * 작성- 한승헌
 * 일시- 2025.11.14
 * 내용- 퀘스트 받는 UI
 * 
 */
UCLASS()
class WANTED_PROJECT4_API UP4QuestWidget : public UP4CustomWidget
{
	GENERATED_BODY()

	//함수 섹션.
public:
	virtual void NativeConstruct() override;
	
	/** 외부에서 퀘스트 코드 넘겨줄 때 호출 */
	void InitWithQuestCode(int32 InQuestCode);

protected:
	UFUNCTION(BlueprintCallable, Category = Quest)
	void OnAcceptClicked(); //수락버튼 클릭할때 발생하는 코드.


	UFUNCTION(BlueprintCallable, Category = Quest)
	void OnDeclinClicked(); //거절버튼 누를때 발생하는 코드.

	//변수 섹션.
public:

protected:
	UPROPERTY(meta =(BindWidget))
	TObjectPtr<class UTextBlock> QuestNameText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> QuestDescText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> StageInfoText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> AcceptButtton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> DeclineButton;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Quest)
	TObjectPtr<class UP4QuestManager> QuestManager;

	int32 PendingQuestCode = -1;
};
