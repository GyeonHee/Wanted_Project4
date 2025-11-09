// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/P4WidgetComponent.h"
#include "P4CustomWidget.h"
void UP4WidgetComponent::InitWidget()
{
	Super::InitWidget();

	UP4CustomWidget* P4GASUserWidget = Cast<UP4CustomWidget>(GetWidget());

	if (P4GASUserWidget != nullptr)
	{

	}
}
