// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "GamepadUIGameMode.h"
#include "GamepadUIHUD.h"
#include "GamepadUICharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "RPGController.h"

AGamepadUIGameMode::AGamepadUIGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AGamepadUIHUD::StaticClass();

	PlayerControllerClass = ARPGController::StaticClass();
}
