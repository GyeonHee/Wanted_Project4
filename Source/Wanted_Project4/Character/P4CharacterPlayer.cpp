// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/P4CharacterPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "AbilitySystemComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/SceneComponent.h"

AP4CharacterPlayer::AP4CharacterPlayer()
{
	//bUseControllerRotationPitch = false;
	//bUseControllerRotationRoll = false;
	//bUseControllerRotationYaw = false;

	//GetCharacterMovement()->bOrientRotationToMovement = true;
	//GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	//GetCharacterMovement()->JumpZVelocity = 300.0f;
	//
	//// 
	//GetMesh()->SetRelativeLocationAndRotation(
	//	FVector(0.0f, 0.0f, -38.0f),
	//	FRotator(0.0f, -90.0f, 0.0f)
	//);

	//// Set Assets
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMesh(
	//	TEXT("/Game/Character/Model/Hunter_King/King.King"));
	//if (CharacterMesh.Succeeded())
	//{
	//	GetMesh()->SetSkeletalMesh(CharacterMesh.Object);
	//}

	//static ConstructorHelpers::FClassFinder<UAnimInstance> CharacterAnim(
	//	TEXT("/Game/Character/Animation/ABP_P4Character.ABP_P4Character_C"));
	//if (CharacterAnim.Succeeded())
	//{
	//	GetMesh()->SetAnimInstanceClass(CharacterAnim.Class);
	//}

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 350.f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	
	//미니맵을 위한 코드입니다.
	//-작성: 한승헌 -일시: 2025.11.07
	MapSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MiniMap SpringArm"));
	MapSpringArm->SetupAttachment(RootComponent);
	MapSpringArm->TargetArmLength = 300.0f;
	MapSpringArm->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	MapSpringArm->bUsePawnControlRotation = false;  // 컨트롤러 회전 영향 X
	MapSpringArm->bDoCollisionTest = false;         // 지형에 밀려 짧아지는 것 방지
	/*Cast<USceneComponent>MapSpringArm->bAbsoluteRotation = true;  */       // 월드 고정 회전

	MapViewrCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MiniMapCapture"));
	MapViewrCapture->SetupAttachment(MapSpringArm);
	MapViewrCapture->ProjectionType = ECameraProjectionMode::Orthographic;
	MapViewrCapture->OrthoWidth = 32768.0f;
	MapViewrCapture->CaptureSource = ESceneCaptureSource::SCS_FinalColorHDR;
	//여기까지가 미니맵 코드입니다. - 작성: 한승헌.
}

void AP4CharacterPlayer::GASInputPressed(int32 InputId)
{
	if (!ASC) return;

	FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(InputId);
	if (Spec)
	{
		Spec->InputPressed = true;

		// 어빌리티 발동 중인가?
		if (Spec->IsActive())
		{
			// 발동 중에 입력 들어옴
			ASC->AbilitySpecInputPressed(*Spec);
		}
		else
		{
			ASC->TryActivateAbility(Spec->Handle);
		}
	}
}

void AP4CharacterPlayer::GASInputReleased(int32 InputId)
{
	if (!ASC) return;

	FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(InputId);
	if (Spec)
	{
		Spec->InputPressed = false;

		if (Spec->IsActive())
		{
			ASC->AbilitySpecInputReleased(*Spec);
		}
	}
}


void AP4CharacterPlayer::HandleMove(const FInputActionValue& Value)
{
	// 입력 값 읽어오기.
	FVector2D Movement = Value.Get<FVector2D>();

	// 이동할 방향 만들기.
	// 카메라가 바라보는 방향(컨트롤러의 방향)을 기준으로 이동 방향 만들기.
	FRotator Rotation = GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	// 앞방향.
	FVector ForwardVector
		= FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	// 오른쪽 방향.
	FVector RightVector
		= FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// 무브먼트에 입력 전달하기.
	// 크기가 1인 숫자를 곱하는 행위는 "회전"
	AddMovementInput(ForwardVector, Movement.Y);
	AddMovementInput(RightVector, Movement.X);
}

void AP4CharacterPlayer::HandleLook(const FInputActionValue& Value)
{
	// 입력 값 읽어오기.
	FVector2D LookValue = Value.Get<FVector2D>();

	// 컨트롤러에 회전 적용.

	// 마우스 좌우 드래그 입력을 컨트롤러의 Z축 회전(요, Yaw)에 적용.
	AddControllerYawInput(LookValue.X);

	// 마우스 좌우 드래그 입력을 컨트롤러의 Y축 회전(피치, Pitch)에 적용.
	AddControllerPitchInput(LookValue.Y);
}

//void AP4CharacterPlayer::SetupHUDWidget(UP4HUDWidget* InHudWidtet)
//{
//	if (InHudWidtet != nullptr)
//	{
//		
//	}
//}

//void AP4CharacterPlayer::HandleAttack(const FInputActionValue& Value)
//{
//	if (UAbilitySystemComponent* ASC = GetAbilitySystemComponent())
//	{
//		ASC->TryActivateAbilityByClass(UBasicAttackAbility::StaticClass());
//	}
//}
