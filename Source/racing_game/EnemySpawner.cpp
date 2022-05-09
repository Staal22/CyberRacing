// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include"Enemy.h"
// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
}
void AEnemySpawner::SpawnEnemy()							//spawns enemy at spawners world location
{
	//get location of spawner
	UWorld* World = GetWorld();
	FVector const Location = GetActorLocation();
	
	if (WhichEnemy == 0) // spawn regular enemy
		{
			AEnemy* EnemyChaser = World->SpawnActor<AEnemy>(ActorToSpawn, Location + FVector(0.f, 0.f, 0.f), GetActorRotation());
			if (EnemyChaser)
			{
				//for broadcasting back to EnemySpawner when Enemy is destroyed
				EnemyChaser->OnEnemyDestruction.AddDynamic(this, &AEnemySpawner::EnemyDestroyed);
			}
		}
	
}
// Called every frame
void AEnemySpawner::Tick(float DeltaTime)					// spawn an enemy if there is currently no enemy spawned and the cooldown (5 secs) is over
{
	Super::Tick(DeltaTime);
	EnemyTime += DeltaTime;
	if (EnemyTime > 5.f && EnemyActive == false)
	{
		EnemyTime = true;
		SpawnEnemy();
	}
}

void AEnemySpawner::EnemyDestroyed()						//starts cooldown timer and enables spawning of further enemies
{
	EnemyTime = 0.f;
	WhichEnemy = 1;
	EnemyActive = false;
	UE_LOG(LogTemp, Warning, TEXT("Enemy respawn initiated"));
}