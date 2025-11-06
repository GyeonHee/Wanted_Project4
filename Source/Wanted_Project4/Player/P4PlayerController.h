// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "P4PlayerController.generated.h"

/**
 * 
 */
class UInputMappingContext;
class UInputAction;

UCLASS()
class WANTED_PROJECT4_API AP4PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    AP4PlayerController();

protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

private:
    // 입력 매핑
    UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<UInputMappingContext> InputMappingContext;

    UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<UInputAction> MoveAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<UInputAction> LookAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<UInputAction> JumpAction;

    //UPROPERTY(EditAnywhere, Category = "Input")
    //TObjectPtr<UInputAction> AttackAction;

private:
    // 입력 처리 함수
    void HandleMove(const FInputActionValue& Value);
    void HandleLook(const FInputActionValue& Value);
    void HandleJumpStart(const FInputActionValue& Value);
    void HandleJumpEnd(const FInputActionValue& Value);
    //void HandleAttack(const FInputActionValue& Value);
};
