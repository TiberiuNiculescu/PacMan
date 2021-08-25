// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PacManHud.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API APacManHud : public AHUD
{
	GENERATED_BODY()

	APacManHud();

	UPROPERTY()
	UFont* HUDFont;

	virtual void DrawHUD() override;
	
};
