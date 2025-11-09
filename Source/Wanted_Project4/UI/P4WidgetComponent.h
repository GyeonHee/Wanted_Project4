// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "P4WidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_PROJECT4_API UP4WidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
protected:
	virtual void InitWidget() override;
};
