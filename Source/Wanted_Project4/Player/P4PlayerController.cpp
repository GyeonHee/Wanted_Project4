// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/P4PlayerController.h"

void AP4PlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Change input mode
	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);

	// todo: need to change for other menus such as Pause, Inventory etc.
	//FInputModeUIOnly
	//FInputModeGameAndUI
}
