// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "CDProjektMatyasikGameMode.h"
#include "CDProjektMatyasikPlayerController.h"
#include "CDProjektMatyasikPawn.h"

ACDProjektMatyasikGameMode::ACDProjektMatyasikGameMode()
{
	// no pawn by default
	DefaultPawnClass = ACDProjektMatyasikPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = ACDProjektMatyasikPlayerController::StaticClass();
}
