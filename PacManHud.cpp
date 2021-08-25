// Fill out your copyright notice in the Description page of Project Settings.


#include "PacManHud.h"
#include "Engine/Canvas.h"
#include "D:\Director lucru\SMPProiect\PacMan\Source\PacMan\PacManGameModeBase.h"
#include "D:\Director lucru\SMPProiect\PacMan\Source\PacMan\Public\PacManCharacter.h"
#include "Kismet/GameplayStatics.h"

APacManHud::APacManHud()
{
	static ConstructorHelpers::FObjectFinder<UFont>HUDFontOb(TEXT("/Engine/EngineFonts/RobotoDistanceField"));
	if (HUDFontOb.Object != NULL) {
		HUDFont = HUDFontOb.Object;
	}
}

void APacManHud::DrawHUD()
{
    FVector2D ScreenDimension = FVector2D(Canvas->SizeX, Canvas->SizeY);

    Super::DrawHUD();

    class APacManGameMode* GameMode = Cast<APacManGameMode>(UGameplayStatics::GetGameMode(this));
    switch (GameMode->GetCurrentState())
    {
        // show a simple menu text
    case EGameState::EMenu:
    {
        DrawText(TEXT("Welcome to Pac Man! \n\n N to start a new game \n P to pause the game"), FColor::White, 50, 50, HUDFont);
    }
    break;

    // show the lifes remains
    case EGameState::EPlaying:
    {
        // get the lives and set them
        APacManCharacter* PacMan = Cast<APacManCharacter>
            (UGameplayStatics::GetPlayerPawn(this, 0));
        if (PacMan)
        {
            FString LivesString = TEXT("Lives: ") +
                FString::FromInt(PacMan->Lives);
            DrawText(LivesString, FColor::Black, 50, 50, HUDFont);
        }
    }
    break;

    // show a gameover text
    case EGameState::EGameOver:
    {
        DrawText(TEXT("GAME OVER! \n\n R to restart"), FColor::White, 50, 50, HUDFont);
    }
    break;

    //show that the game is in paused
    case EGameState::EPause:
    {
        DrawText(TEXT("pause"), FColor::White, 50, 50, HUDFont);
    }
    break;

    // show a win text
    case EGameState::EWin:
    {
        DrawText(TEXT("YOU WIN! \n\n R for another match ;)"), FColor::White, 50, 50, HUDFont);
    }
    break;
    default:
        // nothing
        break;
    }
}