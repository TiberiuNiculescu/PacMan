// Fill out your copyright notice in the Description page of Project Settings.
#include "Enemy.h"
#include "D:\Director lucru\SMPProiect\PacMan\Source\PacMan\PacMan.h"
#include "AIEnemy.h"
#include "Components/CapsuleComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/PrimitiveComponent.h"
#include "D:\Director lucru\SMPProiect\PacMan\Source\PacMan\PacManGameModeBase.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEnemy::AEnemy()
{
	SetActorEnableCollision(true);

	
	GetCapsuleComponent()->SetCapsuleRadius(40.0f);
	GetCapsuleComponent()->SetCapsuleHalfHeight(50.0f);

	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>CylinderObj(TEXT("'/Game/StarterContent/Shapes/Shape_Cylinder'"));
	EnemyBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	EnemyBody->SetStaticMesh(CylinderObj.Object);
	EnemyBody->SetRelativeScale3D(FVector(0.7f, 0.7f, 1.0f));
	EnemyBody->AttachTo(RootComponent);

	
	static ConstructorHelpers::FObjectFinder<UMaterial>VulnerableMat(TEXT("'/Game/M_inamic_Roz_V'"));
	VulnerableMaterial = VulnerableMat.Object;

	// setam calasa noastra AI pentru controller
	AIControllerClass = AAIEnemy::StaticClass();

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	
	DefaultMaterial = EnemyBody->GetMaterial(0);

	
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnCollision);
}

void AEnemy::SetMove(bool moveIt)
{
	
	// casting pentru clasa AI
	AAIEnemy* AI = Cast<AAIEnemy>(AIControllerClass);

	//if (moveIt) { AI->SearchNewPoint(); }
	//else { AI->StopMove(); }

}
void AEnemy::Kill()
{
	
	if (bIsDead) return;

	
	
	bIsDead = true;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}


void AEnemy::Rearm()
{
	bIsDead = false;
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;

	if (bIsVulnerable) { SetInvulnerable(); }
}


void AEnemy::SetVulnerable()
{
	
	GetWorldTimerManager().SetTimer(TimerVulnerable, this, &AEnemy::SetInvulnerable, 10.0f, false);

	
	if (bIsVulnerable) { return; }

	bIsVulnerable = true;

	
	EnemyBody->SetMaterial(0, VulnerableMaterial);

	
	GetCharacterMovement()->MaxWalkSpeed = 50.0f;
}


void AEnemy::SetInvulnerable()
{
	
	GetWorldTimerManager().ClearTimer(TimerVulnerable);

	bIsVulnerable = false;

	
	EnemyBody->SetMaterial(0, DefaultMaterial);

	
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
}

void AEnemy::OnCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APacManCharacter::StaticClass()))
	{
		
		
		if (bIsVulnerable) { Kill(); }
		else
		{
			
			APacManCharacter* PacMan = Cast<APacManCharacter>(OtherActor);
			PacMan->Kill();
		}
	}
}


// Called to bind functionality to input
/*void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
*/

