// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GA/AT/P4AT_JumpAndWaitForLanding.h"
#include "P4AT_JumpAndWaitForLanding.h"
#include "GameFramework/Character.h"

UP4AT_JumpAndWaitForLanding::UP4AT_JumpAndWaitForLanding()
{
}

UP4AT_JumpAndWaitForLanding* UP4AT_JumpAndWaitForLanding::CreateTask(UGameplayAbility* OwningAbility)
{
	UP4AT_JumpAndWaitForLanding* NewTask = NewAbilityTask<UP4AT_JumpAndWaitForLanding>(OwningAbility);
	return NewTask;
}

void UP4AT_JumpAndWaitForLanding::Activate()
{
	Super::Activate();

	ACharacter* Character = CastChecked<ACharacter>(GetAvatarActor());
	Character->LandedDelegate.AddDynamic(this, &UP4AT_JumpAndWaitForLanding::OnLandedCallback);
	Character->Jump();

	SetWaitingOnAvatar();
}

void UP4AT_JumpAndWaitForLanding::OnDestroy(bool AbilityEnded)
{
	ACharacter* Character = CastChecked<ACharacter>(GetAvatarActor());
	Character->LandedDelegate.RemoveDynamic(this, &UP4AT_JumpAndWaitForLanding::OnLandedCallback);

	Super::OnDestroy(AbilityEnded);
}

void UP4AT_JumpAndWaitForLanding::OnLandedCallback(const FHitResult& Hit)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnComplete.Broadcast();
	}
}
