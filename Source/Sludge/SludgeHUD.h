// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SludgeHUD.generated.h"

UCLASS()
class ASludgeHUD : public AHUD
{
	GENERATED_BODY()

public:
	ASludgeHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	
	//UTexture2D* CrosshairTex;

};

