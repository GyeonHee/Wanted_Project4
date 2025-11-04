// Fill out your copyright notice in the Description page of Project Settings.


#include "P4CharacterBase.h"
#include "AbilitySystemComponent.h"

// Sets default values
AP4CharacterBase::AP4CharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
}

void AP4CharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ASC->InitAbilityActorInfo(this, this);
}

UAbilitySystemComponent* AP4CharacterBase::GetAbilitySystemComponent() const
{
	return ASC;
}

void AP4CharacterBase::AttackHitCheck()
{
	// 충돌 판정 로직 작성.
}

// Called when the game starts or when spawned
void AP4CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AP4CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AP4CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

