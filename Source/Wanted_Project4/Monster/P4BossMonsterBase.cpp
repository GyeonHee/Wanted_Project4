// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/P4BossMonsterBase.h"

// Sets default values
AP4BossMonsterBase::AP4BossMonsterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AP4BossMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AP4BossMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AP4BossMonsterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

