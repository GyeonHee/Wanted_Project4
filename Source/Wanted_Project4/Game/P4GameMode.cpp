// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/P4GameMode.h"

AP4GameMode::AP4GameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> P4CharacterClassRef(TEXT("/Script/Wanted_Project4.P4CharacterPlayer"));
	if(P4CharacterClassRef.Succeeded())
	{
		DefaultPawnClass = P4CharacterClassRef.Class;
	}
	
	static ConstructorHelpers::FClassFinder<APlayerController> P4PlayerControllerClassRef(TEXT("/Script/Wanted_Project4.P4PlayerController"));
	if (P4PlayerControllerClassRef.Succeeded())
	{
		PlayerControllerClass = P4PlayerControllerClassRef.Class;
	}
	
}
