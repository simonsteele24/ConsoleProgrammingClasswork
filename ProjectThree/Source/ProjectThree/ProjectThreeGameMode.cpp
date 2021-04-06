// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectThreeGameMode.h"
#include "ProjectThreeHUD.h"
#include "ProjectThreeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectThreeGameMode::AProjectThreeGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AProjectThreeHUD::StaticClass();
}
