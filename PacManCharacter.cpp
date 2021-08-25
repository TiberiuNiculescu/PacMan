// Fill out your copyright notice in the Description page of Project Settings.
#include "PacManCharacter.h"
#include "D:\Director lucru\SMPProiect\PacMan\Source\PacMan\PacMan.h"
#include "D:\Director lucru\SMPProiect\PacMan\Source\PacMan\PacManGameModeBase.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
#include "Collectable.h"
#include "Components/CapsuleComponent.h"

#include "Components/PrimitiveComponent.h"
#include "EngineUtils.h"

// Sets default values
APacManCharacter::APacManCharacter()
{
 	
	
	SetActorEnableCollision(true);
	
}

// Called when the game starts or when spawned
void APacManCharacter::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<APacManGameMode>(UGameplayStatics::GetGameMode(this));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APacManCharacter::OnCollision);
	
	for (TActorIterator<ACollectable> CollectableItr(GetWorld()); CollectableItr; ++CollectableItr)
	{
		CollectablesToEat++;
	}
	StartPoint = GetActorLocation();  
	Lives = 3;  
	
}




// Called to bind functionality to input
void APacManCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// bind the input from the player
	InputComponent->BindAxis("MoveX", this, &APacManCharacter::MoveXAxis);
	InputComponent->BindAxis("MoveY", this, &APacManCharacter::MoveYAxis);
	InputComponent->BindAction("NewGame", IE_Pressed, this, &APacManCharacter::NewGame);
	InputComponent->BindAction("Pause", IE_Pressed, this, &APacManCharacter::Pause);
	InputComponent->BindAction("Restart", IE_Pressed, this, &APacManCharacter::RestartGame);

}

void APacManCharacter::MoveXAxis(float AxisValue)
{
	CurrentVelocity.X = AxisValue;
	AddMovementInput(CurrentVelocity);

}

void APacManCharacter::MoveYAxis(float AxisValue)
{
	CurrentVelocity.Y = AxisValue;
	AddMovementInput(CurrentVelocity);
}

void APacManCharacter::NewGame()
{
	if (GameMode->GetCurrentState() == EGameState::EMenu) {
		GameMode->SetCurrentState(EGameState::EPlaying);
	}
}


void APacManCharacter::Pause()
{
	if (GameMode->GetCurrentState() == EGameState::EPlaying) {
		GameMode->SetCurrentState(EGameState::EPause);
	}
	else if (GameMode->GetCurrentState() == EGameState::EPause) {
		GameMode->SetCurrentState(EGameState::EPlaying);
	}
}


void APacManCharacter::RestartGame()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("RestartLevel"));
}

void APacManCharacter::OnCollision(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (GameMode->GetCurrentState() == EGameState::EPlaying)
	{
		
		if (OtherActor->IsA(ACollectable::StaticClass()))
		{
			if (--CollectablesToEat == 0) {
				GameMode->SetCurrentState(EGameState::EWin);
			}
			
			OtherActor->Destroy();
		}
	}
}

void APacManCharacter::Kill()
{
	if (--Lives == 0) {
		GameMode->SetCurrentState(EGameState::EGameOver);
	}
	else{
	  SetActorLocation(StartPoint);
	}
}

