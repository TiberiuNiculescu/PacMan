// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "Enemy.h"
#include "AIEnemy.generated.h"

/**
 *
 */
UCLASS()
class PACMAN_API AAIEnemy : public AAIController
{
	GENERATED_BODY()

public:

	AAIEnemy();

	void OnPossess(class APawn* InPawn) override;

	//virtual void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result) override;

	//void SearchNewPoint();
	void GoHome();
	void Rearm();
	void StopMove();

private:

	class AEnemy* Bot;
	FVector HomeLocation;
	FTimerHandle TimerDead;
};