// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "D:\Director lucru\SMPProiect\PacMan\Source\PacMan\PacManGameModeBase.h"
#include "Components/PrimitiveComponent.h"
#include "PacManCharacter.generated.h"

UCLASS()
class PACMAN_API APacManCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APacManCharacter();
	virtual void BeginPlay() override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	void Kill();
	uint8 Lives;  // player total lives

private:
	
	UFUNCTION()
		void OnCollision( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// movement handlers
	void MoveXAxis(float AxisValue);
	void MoveYAxis(float AxisValue);

	// key events
	void NewGame();
	void Pause();
	void RestartGame();

	FVector CurrentVelocity;// the current velocity of the player
	APacManGameMode* GameMode; // pointer to the game mode
	uint8 CollectablesToEat;  // total collectables in order to win
	FVector StartPoint;  // the start point of the player

	



};
