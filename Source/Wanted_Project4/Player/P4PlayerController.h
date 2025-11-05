// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "P4PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_PROJECT4_API AP4PlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

};
