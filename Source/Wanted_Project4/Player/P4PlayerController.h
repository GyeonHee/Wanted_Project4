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
class UAbilitySystemComponent;

UCLASS()
class WANTED_PROJECT4_API AP4PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    AP4PlayerController();

protected:
    virtual void BeginPlay() override;
    virtual void OnPossess(APawn* InPawn) override;

    // 입력 바인딩
    virtual void SetupInputComponent() override;
    // GAS 입력 바인딩
    void SetupGASInputBindings(UAbilitySystemComponent* ASC);

private:
    // 입력 매핑
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputMappingContext> InputMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> JumpAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> AttackAction;

private:
    // GAS 
    void HandleAbilityPressed(int32 InputID);
    void HandleAbilityReleased(int32 InputID);
    // 입력 처리 함수
    void HandleMove(const FInputActionValue& Value);
    void HandleLook(const FInputActionValue& Value);
};
