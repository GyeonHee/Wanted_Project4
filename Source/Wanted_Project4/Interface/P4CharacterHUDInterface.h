// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "P4CharacterHUDInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UP4CharacterHUDInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WANTED_PROJECT4_API IP4CharacterHUDInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	//HUD 호출 인터페이스 함수.
	virtual void SetupHUDWidget(class UP4HUDWidget* HudWidget) = 0;
};
