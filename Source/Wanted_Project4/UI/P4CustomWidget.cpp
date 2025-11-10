// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/P4CustomWidget.h"
#include "AbilitySystemBlueprintLibrary.h"

//累己 茄铰清
void UP4CustomWidget::SetAbilitySystemComponent(AActor* InOwner)
{
    if (IsValid(InOwner) == true)
    {
        ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InOwner);
    }
}

//累己 茄铰清
UAbilitySystemComponent* UP4CustomWidget::GetAbilitySystemComponent() const
{
    return ASC;
}
