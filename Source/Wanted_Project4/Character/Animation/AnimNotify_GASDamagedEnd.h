// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_GASDamagedEnd.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_PROJECT4_API UAnimNotify_GASDamagedEnd : public UAnimNotify
{
	GENERATED_BODY()

public:
	UAnimNotify_GASDamagedEnd();

protected:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
