// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_GrabKatana.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_PROJECT4_API UAnimNotify_GrabKatana : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotify_GrabKatana();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
