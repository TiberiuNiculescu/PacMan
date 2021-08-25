// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Runtime\Engine\Classes\Components\SphereComponent.h>
#include "Collectable.generated.h"


UCLASS()
class PACMAN_API ACollectable : public AActor
{
	GENERATED_BODY()
		//Line skip 1
		//Line skip 2
public:
	// Sets default values for this actor's properties
	ACollectable();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = Collectable)
		USphereComponent* BaseCollisionComponent;

	UPROPERTY(EditDefaultsOnly, Category = Collectable)
		UStaticMeshComponent* CollectableMesh;

	UPROPERTY(EditAnywhere, Category = Collectable)
		bool bIsSuperCollectable;

};
