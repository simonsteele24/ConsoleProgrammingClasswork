// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectThreeGameMode.h"
#include "ProjectThreeHUD.h"
#include "ProjectThreeCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/GameState.h"

AProjectThreeGameMode::AProjectThreeGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// set default game state class to our blueprinted game state instance
	static ConstructorHelpers::FClassFinder<AGameStateBase> GameStateClassFinder(TEXT("/Game/Blueprints/BP_FPGameState"));
	GameStateClass = GameStateClassFinder.Class;

	// use our custom HUD class
	HUDClass = AProjectThreeHUD::StaticClass();
}
