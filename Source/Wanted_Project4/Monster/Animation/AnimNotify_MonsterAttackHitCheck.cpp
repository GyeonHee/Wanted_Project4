// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_MonsterAttackHitCheck.h"
#include "Wanted_Project4/Interface/AnimationAttackInterface.h"


void UAnimNotify_MonsterAttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                               const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		// MeshComponent 를 갖고있는 Actor 에 붙어있는 AnimationAttackInterface 불러오기
		IAnimationAttackInterface* AttackPawn
			= Cast<IAnimationAttackInterface>(MeshComp->GetOwner());
		if (AttackPawn)
		{
			// 있다면 AttackHitCheck 호출
			AttackPawn->AttackHitCheck();
		}
	}
}
