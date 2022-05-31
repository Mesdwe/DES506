// Copyright Epic Games, Inc. All Rights Reserved.

#include "SludgeGameMode.h"
#include "SludgeHUD.h"
#include "SludgeCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASludgeGameMode::ASludgeGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ASludgeHUD::StaticClass();
}
