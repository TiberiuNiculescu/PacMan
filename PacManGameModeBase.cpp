
/// Fill out your copyright notice in the Description page of Project Settings.
#include "D:\Director lucru\SMPProiect\PacMan\Source\PacMan\PacManGameModeBase.h"
#include "PacMan.h"
#include "Enemy.h"
#include "AIEnemy.h"
#include "EngineUtils.h"
#include "PacManHud.h"




APacManGameMode::APacManGameMode()
{
	
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnOb(TEXT("'/Game/BP_Pacman'"));
	if (PlayerPawnOb.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnOb.Class;
	}
	HUDClass = APacManHud::StaticClass();
}

void APacManGameMode::BeginPlay()
{
	currentState = EGameState::EMenu;

	
	PC = GetWorld()->GetFirstPlayerController();

	
	for (TActorIterator<AEnemy> enemyIt(GetWorld()); enemyIt; ++enemyIt)
	{
		AEnemy* enemy = Cast< AEnemy >(*enemyIt);
		if (enemy)	Enemies.Add(enemy);
	}
	
}

EGameState APacManGameMode::GetCurrentState() const
{
	return currentState;

}



void APacManGameMode::SetCurrentState(EGameState value)
{
	currentState = value;

	
	
	switch (value)
	{
		
	case EGameState::EPlaying:		
		
		// incepe miscarea fantomelor
		/*for (auto Iter(Enemies.CreateIterator()); Iter; Iter++) {
			(*Iter)->SetMove(true);
		}
		break;
		*/
	case EGameState::EGameOver:
		// inlaturam inamicii
		for (auto Iter(Enemies.CreateIterator()); Iter; Iter++) {
			(*Iter)->Destroy();
		}
		break;


		
	case EGameState::EWin:

		// inlaturam din nou inamicii
		for (auto Iter(Enemies.CreateIterator()); Iter; Iter++) {
			(*Iter)->Destroy();
		}
		break;

		/*
	case EGameState::EPause:

		for (auto Iter(Enemies.CreateIterator()); Iter; Iter++) {
			(*Iter)->SetMove(false);
		}
		break;
		*/
	default:
		
		break;
	}
	

}



void APacManGameMode::SetEnemyVulnerable()
{
	for (auto Iter(Enemies.CreateIterator()); Iter; Iter++) {
		(*Iter)->SetVulnerable();
	}

}
