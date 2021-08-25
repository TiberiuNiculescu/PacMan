// Fill out your copyright notice in the Description page of Project Settings.
#include "AIEnemy.h"
#include "D:\Director lucru\SMPProiect\PacMan\Source\PacMan\PacMan.h"
#include "Engine/StaticMesh.h"
#include "NavigationSystem.h"
//#include "C:\Program Files\UE_4.26\Engine\Source\Runtime\Engine\Classes\AI\NavigationSystemConfig.h"
//#include "C:\Program Files\UE_4.26\Engine\Source\Runtime\Engine\Classes\AI\NavigationSystemBase.h"

AAIEnemy::AAIEnemy() {}


void AAIEnemy::OnPossess(class APawn* InPawn)
{
	Super::Possess(InPawn);

	Bot = Cast<AEnemy>(InPawn);

	HomeLocation = Bot->GetActorLocation();
	//SearchNewPoint();
}


void AAIEnemy::GoHome()
{
	MoveToLocation(HomeLocation);
	GetWorldTimerManager().SetTimer(TimerDead, this, &AAIEnemy::Rearm, 5.0f, false);
}


void AAIEnemy::Rearm()
{
	GetWorldTimerManager().ClearTimer(TimerDead);
	Bot->Rearm();
}


/*void AAIEnemy::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	if (!Bot->bIsDead) { SearchNewPoint(); }
}
*/
// stop the pawn movements
void AAIEnemy::StopMove()
{
	StopMovement();

}

/* void AAIEnemy::SearchNewPoint()
{
	UNavigationSystemV1* NavMesh = UNavigationSystemV1::GetCurrent(this);

	if (NavMesh)
	{
		const float SearchRadius = 10000.0f;
		FNavLocation RandomPt;
		const bool bFound = NavMesh->GetRandomReachablePointInRadius(Bot->GetActorLocation(), SearchRadius, RandomPt);
		if (bFound)
		{
			MoveToLocation(RandomPt.Location);
		}
	}
}
*/