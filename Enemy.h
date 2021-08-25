// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
//#include "AIEnemy.h"
#include "PacManCharacter.h"
#include "Enemy.generated.h"

UCLASS()
class PACMAN_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	UFUNCTION()
		void OnCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// facem editabil pentru setarea materialului
	UPROPERTY(EditDefaultsOnly, Category = Body)
		UStaticMeshComponent* EnemyBody;

	void SetVulnerable();
	void SetInvulnerable();

	void SetMove(bool MoveIt);
	void Kill();
	void Rearm();

	bool bIsDead;

private:

	bool bIsVulnerable;

	FTimerHandle TimerVulnerable;

	class UMaterialInterface* DefaultMaterial;
	class UMaterialInterface* VulnerableMaterial;


};
