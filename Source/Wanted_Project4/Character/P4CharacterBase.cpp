// Fill out your copyright notice in the Description page of Project Settings.


#include "P4CharacterBase.h"
#include "AbilitySystemComponent.h"
#include "Attribute/P4PlayerAttributeSet.h"
#include "Physics/P4Collision.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"

// -작성: 노현기 -일시: 2025.11.10
// Todo: 인벤토리 컴포넌트 클래스 폴더 위치를 컴포넌트로 옮길 것
#include "Inventory/P4InventoryComponent.h"
#include "Item/ItemDataBase.h"
#include "UI/P4InventoryWidget.h"

// Sets default values
AP4CharacterBase::AP4CharacterBase()
{
	//PrimaryActorTick.bCanEverTick = true;

	// GAS 초기화
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	AttributeSet = CreateDefaultSubobject<UP4PlayerAttributeSet>(TEXT("AttributeSet"));

	// -작성: 노현기 -일시: 2025.11.10
	// 인벤토리 컴포넌트 생성
	InventoryComp = CreateDefaultSubobject<UP4InventoryComponent>(TEXT("InventoryComponent"));

	// Pawn
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Capsule
	//GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(CPROPILE_P4CAPSULE);

	// Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	//GetCharacterMovement()->AirControl = 0.35f;
	//GetCharacterMovement()->MaxWalkSpeed = 500.f;
	//GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	//GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Mesh
	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.0f, 0.0f, -38.0f),
		FRotator(0.0f, -90.0f, 0.0f)
	);
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	// Set Assets
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(
		TEXT("/Game/Character/Model/Hunter_King/King.King"));
	if (CharacterMeshRef.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(
		TEXT("/Game/Character/Animation/ABP_P4Character.ABP_P4Character_C"));
	if (AnimInstanceClassRef.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}

	//static ConstructorHelpers::FObjectFinder<UABCharacterControlData> ShoulderDataRef(TEXT("/Script/ArenaBattle.ABCharacterControlData'/Game/ArenaBattle/CharacterControl/ABC_Shoulder.ABC_Shoulder'"));
	//if (ShoulderDataRef.Object)
	//{
	//	CharacterControlManager.Add(ECharacterControlType::Shoulder, ShoulderDataRef.Object);
	//}

	//static ConstructorHelpers::FObjectFinder<UABCharacterControlData> QuaterDataRef(TEXT("/Script/ArenaBattle.ABCharacterControlData'/Game/ArenaBattle/CharacterControl/ABC_Quater.ABC_Quater'"));
	//if (QuaterDataRef.Object)
	//{
	//	CharacterControlManager.Add(ECharacterControlType::Quater, QuaterDataRef.Object);
	//}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboActionMontageRef(TEXT("/Game/Character/Animation/Katana/ForUse/AM_KatanaDefaultAttack.AM_KatanaDefaultAttack"));
	if (ComboActionMontageRef.Object)
	{
		DefaultAttackMontage = ComboActionMontageRef.Object;
	}

	//static ConstructorHelpers::FObjectFinder<UABComboActionData> ComboActionDataRef(TEXT("/Script/ArenaBattle.ABComboActionData'/Game/ArenaBattle/CharacterAction/ABA_ComboAttack.ABA_ComboAttack'"));
	//if (ComboActionDataRef.Object)
	//{
	//	ComboActionData = ComboActionDataRef.Object;
	//}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeadMontageRef(TEXT("/Game/Character/Animation/AM_Dead.AM_Dead"));
	if (DeadMontageRef.Object)
	{
		DeadMontage = DeadMontageRef.Object;
	}

	// Weapon Component
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), TEXT("hand_lSocket"));

	//todo: Load Weapon through Inventory
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMeshRef(
		TEXT("/Game/Weapon/Katana.Katana"));
	if (WeaponMeshRef.Succeeded())
	{
		Weapon->SetSkeletalMesh(WeaponMeshRef.Object);
	}
	
}

void AP4CharacterBase::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    if (ASC)
    {
        ASC->InitAbilityActorInfo(this, this);
        //AttributeSet = NewObject<UP4PlayerAttributeSet>(this, UP4PlayerAttributeSet::StaticClass());
    }
	UP4PlayerAttributeSet* PlayerAttributeSet = Cast<UP4PlayerAttributeSet>(AttributeSet);
	PlayerAttributeSet->OnHpZero.AddUObject(this, &AP4CharacterBase::SetDead);
}

void AP4CharacterBase::SetDead()
{
	// 이동 못하게 막기
	GetCharacterMovement()->SetMovementMode(MOVE_None);

	// 사망 몽타주 재생
	PlayDeadAnimation();

	// 콜리전 끄기
	SetActorEnableCollision(false);

	// DeadEventDelayTime 후 액터 삭제
	//FTimerHandle DeadTimerHandle;
	//float DeadEventDelayTime = 5.f;
	//GetWorld()->GetTimerManager().SetTimer(
	//	DeadTimerHandle,
	//	[&]()
	//	{
	//		Destroy();
	//	},
	//	DeadEventDelayTime,
	//	false
	//);
}

void AP4CharacterBase::PlayDeadAnimation()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->StopAllMontages(0.f);

		const float PlayRate = 3.0f;
		AnimInstance->Montage_Play(DeadMontage, PlayRate);
	}
}

// -작성: 노현기 -일시: 2025.11.10
void AP4CharacterBase::BeginPlay()
{
	Super::BeginPlay();

	// 테스트용 아이템 추가 (UI는 컨트롤러가 담당)
	if (InventoryComp)
	{
		UItemDataBase* TestSword = LoadObject<UItemDataBase>(nullptr,
			TEXT("/Game/Item/Equipment/DA_Sword.DA_Sword"));
		UItemDataBase* TestShield = LoadObject<UItemDataBase>(nullptr,
			TEXT("/Game/Item/Equipment/DA_Shield.DA_Shield"));
		UItemDataBase* TestPotion = LoadObject<UItemDataBase>(nullptr,
			TEXT("/Game/Item/Consumable/DA_HealthPotion.DA_HealthPotion"));
		UItemDataBase* TestPotion2 = LoadObject<UItemDataBase>(nullptr,
			TEXT("/Game/Item/Consumable/DA_IncreaseMaxHealthPotion.DA_IncreaseMaxHealthPotion"));

		if (TestSword)
		{
			InventoryComp->AddItem(TestSword, 1);
			UE_LOG(LogTemp, Warning, TEXT("검 추가됨!"));
			InventoryComp->AddItem(TestSword, 1);
			UE_LOG(LogTemp, Warning, TEXT("검 1개 더 추가됨!"));
			InventoryComp->AddItem(TestShield, 1);
		}

		if (TestPotion)
		{
			InventoryComp->AddItem(TestPotion, 10);
			UE_LOG(LogTemp, Warning, TEXT("포션 10개 추가됨!"));
			InventoryComp->AddItem(TestPotion, 5);
			UE_LOG(LogTemp, Warning, TEXT("포션 5개 더 추가됨!"));
			InventoryComp->AddItem(TestPotion, 99);
			InventoryComp->AddItem(TestPotion, 90);
			InventoryComp->AddItem(TestPotion2, 50);
		}
	}
}

UAbilitySystemComponent* AP4CharacterBase::GetAbilitySystemComponent() const
{
	return ASC;
}

//void AP4CharacterBase::AttackHitCheck()
//{
//	// 충돌 판정 로직 작성.
//}


