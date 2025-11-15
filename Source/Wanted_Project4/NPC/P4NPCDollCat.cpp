// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/P4NPCDollCat.h"

AP4NPCDollCat::AP4NPCDollCat()
{

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletaMeshRef(TEXT("/Game/NPC/DollCat/DollCat.DollCat"));

	if (SkeletaMeshRef.Succeeded() == true)
	{
		GetMesh()->SetSkeletalMesh(SkeletaMeshRef.Object);
	}


	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.0f, 0.0f, -90.0f),
		FRotator(0.0f, -90.0f, 0.0f)
	);

	//임시 테스트 ABP
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceRef(TEXT("/Game/NPC/Dollcat/Animations/ABP_NPCTest.ABP_NPCTest_C"));

	if (AnimInstanceRef.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceRef.Class);
	}

	Tag_InRange = FGameplayTag::RequestGameplayTag(FName("Character.Interaction.Quest"));
	ReportObjectiveID = "Report_Jagras";
}

void AP4NPCDollCat::BeginPlay()
{
	Super::BeginPlay();
	NPCQuestCode = 1;
}

void AP4NPCDollCat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AP4NPCDollCat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AP4NPCDollCat::Interaction(ACharacter* Character)
{
	Super::Interaction(Character);
}


UAbilitySystemComponent* AP4NPCDollCat::GetAbilitySystemComponent() const
{
	Super::GetAbilitySystemComponent();

	return nullptr;
}
