// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
//#include "Enemy.h"
//#include "PacManCharacter.h"
//#include "PacManHUD.h"
#include "PacManGameModeBase.generated.h"

enum class EGameState : short
{
	EMenu,
	EPlaying,
	EPause,
	EWin,
	EGameOver
};


/**
 *
 */
UCLASS()
class PACMAN_API APacManGameMode : public AGameMode
{
	GENERATED_BODY()


public:
	
	APacManGameMode();
	
	virtual void BeginPlay() override;

	
	EGameState GetCurrentState() const;

	
	void SetCurrentState(EGameState value);

	void SetEnemyVulnerable();

private:
	EGameState currentState;
	
		TArray<class AEnemy*> Enemies;
		class APlayerController* PC;

	
};
/*FORCEINLINE EGameState APacManGameMode::GetCurrentState() const
{
	return currentState;
};*/
