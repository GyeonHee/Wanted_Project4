// Fill out your copyright notice in the Description page of Project Settings.
/**
*작성: 한승헌
* 일시: 2025.11.12
* NPC 관련 코드입니다.
* GAS연동하여 퀘스트 기능 추가하겠습니다.
**/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "P4NPCBase.generated.h"

UCLASS()
class WANTED_PROJECT4_API AP4NPCBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AP4NPCBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	virtual void Interaction(ACharacter* Character);

	FORCEINLINE int32 GetNPCQuestCode() const
	{
		return NPCQuestCode;
	}

protected:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//GAS 섹션.
public:
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<class UAbilitySystemComponent> N_ASC; //NPC의 어빌리티 시스템 컴포넌트.

	UPROPERTY(EditAnywhere, Category = "GAS")
	FGameplayTag Tag_InRange;

	//기타 변수 및 컴포넌트 섹션.
public:

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class USphereComponent> InteractionSphere; //인터렉션 범위

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Quest)
	int32 NPCQuestCode;

};
