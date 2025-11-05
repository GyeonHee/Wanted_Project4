// Fill out your copyright notice in the Description page of Project Settings.


#include "P4MonsterJagras.h"

#include "Components/BoxComponent.h"

AP4MonsterJagras::AP4MonsterJagras()
{	
	// Mesh 설정
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -80.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	// Box Collision 설정
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxCollision->SetupAttachment(GetMesh(), TEXT("Armature_ems049_00"));
	BoxCollision->SetRelativeLocation(FVector(0.f, -64.f, -90.f));
	BoxCollision->SetBoxExtent(FVector(30.f, 65.f, 165.f));
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshRef(
		TEXT("/Game/Monster/Model/Jagras/Jagras.Jagras")
	);
	if (MeshRef.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceRef(
		TEXT("/Game/Monster/Animation/ABP_Jagras.ABP_Jagras_C")
	);
	if (AnimInstanceRef.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceRef.Class);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackActionMontageRef(
		TEXT("/Game/Monster/Model/Jagras/AM_Jagras_Attack.AM_Jagras_Attack")
	);
	if (AttackActionMontageRef.Succeeded())
	{
		AttackActionMontage = AttackActionMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeadMontageRef(
		TEXT("/Game/Monster/Model/Jagras/AM_Jagras_Dead.AM_Jagras_Dead")
	);
	if (DeadMontageRef.Succeeded())
	{
		DeadMontage = DeadMontageRef.Object;
	}
}
