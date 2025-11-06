// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/P4TestGameMode.h"
#include "Test/P4TestPlayerController.h"
#include "Test/P4TestCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

AP4TestGameMode::AP4TestGameMode()
{
	PlayerControllerClass = AP4TestPlayerController::StaticClass();
	DefaultPawnClass = nullptr;
}
