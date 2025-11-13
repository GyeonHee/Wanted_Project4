// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/Anim/P4NPCAnimationInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
UP4NPCAnimationInstance::UP4NPCAnimationInstance()
{

}

void UP4NPCAnimationInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ACharacter>(GetOwningActor());

	if (Owner != nullptr)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void UP4NPCAnimationInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}
