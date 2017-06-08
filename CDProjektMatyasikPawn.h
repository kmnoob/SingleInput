// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CDProjektMatyasikPawn.generated.h"

UCLASS(config=Game)
class ACDProjektMatyasikPawn : public APawn
{
	
	GENERATED_UCLASS_BODY()
	

public:

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;

protected:

	void TriggerInput();
	void TriggerRelease();
	int ConvertTimerToMorse(float interval);
	FTimerHandle InputTimer;
	float GetInputTime();
	void ClearTimer();
	TArray<int32> PlayerMorseVector;
	TArray<int32> TargetMorseVector;
	

};
