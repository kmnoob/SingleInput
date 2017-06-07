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
}

void ACDProjektMatyasikPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		{
			FVector Start, Dir, End;
			PC->DeprojectMousePositionToWorld(Start, Dir);
			End = Start + (Dir * 8000.0f);
			TraceForBlock(Start, End, false);
		}
	}
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
	if (CurrentBlockFocus)
	{
		CurrentBlockFocus->HandleClicked();
		GetWorldTimerManager().SetTimer(InputTimer, 5.0f, false);
	}
}

void ACDProjektMatyasikPawn::TriggerRelease()
{
	ClearTimer();
}

void ACDProjektMatyasikPawn::TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers)
{
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);
	if (bDrawDebugHelpers)
	{
		DrawDebugLine(GetWorld(), Start, HitResult.Location, FColor::Red);
		DrawDebugSolidBox(GetWorld(), HitResult.Location, FVector(20.0f), FColor::Red);
	}
	if (HitResult.Actor.IsValid())
	{
		ACDProjektMatyasikBlock* HitBlock = Cast<ACDProjektMatyasikBlock>(HitResult.Actor.Get());
		if (CurrentBlockFocus != HitBlock)
		{
			if (CurrentBlockFocus)
			{
				CurrentBlockFocus->Highlight(false);
			}
			if (HitBlock)
			{
				HitBlock->Highlight(true);
			}
			CurrentBlockFocus = HitBlock;
		}
	}
	else if (CurrentBlockFocus)
	{
		CurrentBlockFocus->Highlight(false);
		CurrentBlockFocus = nullptr;
	}
}

float ACDProjektMatyasikPawn::GetInputTime()
{
	float  Elapsed = GetWorldTimerManager().GetTimerElapsed(InputTimer);
	return Elapsed;
}

void ACDProjektMatyasikPawn::ClearTimer()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Some variable values: x: %f"), GetInputTime()));
	GetWorldTimerManager().ClearTimer(InputTimer);
	
}
