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

	// 인벤토리 토글 함수
	void ToggleInventory();

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UP4CustomWidget> InventoryWidgetClass;

private:
	UPROPERTY(EditAnywhere, Category = "UI")
	TObjectPtr<class UP4CustomWidget> InventoryWidget;

	bool bIsInventoryVisible = false;
};
