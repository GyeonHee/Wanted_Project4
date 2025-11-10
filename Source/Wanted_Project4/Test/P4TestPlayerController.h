// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "P4TestPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_PROJECT4_API AP4TestPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AP4TestPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

protected:
	// 캐릭터에 빙의했을 때 호출
	virtual void OnPossess(APawn* InPawn) override;

	// 인벤토리 토글 함수
	void ToggleInventory();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UP4InventoryWidget> InventoryWidgetClass;

private:
	UPROPERTY()
	TObjectPtr<class UP4InventoryWidget> InventoryWidget;

	bool bIsInventoryVisible = false;
};
