// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "CDProjektMatyasikPawn.h"
#include "CDProjektMatyasikBlock.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

//// wywalic to potem
#include "Engine.h"
//

ACDProjektMatyasikPawn::ACDProjektMatyasikPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	int32 tableinit[] = { 0,1,0,1,1};
	TargetMorseVector.Append(tableinit, ARRAY_COUNT(tableinit));
}

void ACDProjektMatyasikPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void ACDProjektMatyasikPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Input", EInputEvent::IE_Pressed, this, &ACDProjektMatyasikPawn::TriggerInput);
	PlayerInputComponent->BindAction("Input", EInputEvent::IE_Released, this, &ACDProjektMatyasikPawn::TriggerRelease);
}

void ACDProjektMatyasikPawn::CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult)
{
	Super::CalcCamera(DeltaTime, OutResult);

	OutResult.Rotation = FRotator(-90.0f, -90.0f, 0.0f);
}



void ACDProjektMatyasikPawn::TriggerInput()
{
		GetWorldTimerManager().SetTimer(InputTimer, 5.0f, false);

}

void ACDProjektMatyasikPawn::TriggerRelease()
{
	int NewInput = ConvertTimerToMorse(GetInputTime());
	
	PlayerMorseVector.Add(NewInput);
	///////////
	if (PlayerMorseVector.Num() < PlayerMorseVector.Num()) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Something went wrong - PlayerMorseVector.Num() < PlayerMorseVector.Num()")));
		PlayerMorseVector.Empty();
	}
	//////////////////

	if (PlayerMorseVector.Last() == TargetMorseVector[PlayerMorseVector.Num() - 1]) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Some variable values: x: %d"), NewInput));
	}
	else { 
		PlayerMorseVector.Empty();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("WRROONG - EMPTIED")));
	}

	ClearTimer();
}



float ACDProjektMatyasikPawn::GetInputTime()
{
	float  Elapsed = GetWorldTimerManager().GetTimerElapsed(InputTimer);
	return Elapsed;
}

void ACDProjektMatyasikPawn::ClearTimer()
{
	
	GetWorldTimerManager().ClearTimer(InputTimer);
	
}

int ACDProjektMatyasikPawn::ConvertTimerToMorse(float interval)
{
	float threshold = 0.6f;

	if (interval == -1.0f) return 2;	
	if (interval<threshold)  return 0;
	else return 1;
}
