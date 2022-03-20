// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpSpawner.h"
#include "HealthPack.h"
#include "Shotgun.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APowerUpSpawner::APowerUpSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APowerUpSpawner::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void APowerUpSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// spawn a power up if there is currently no power up spawned and the cooldown (5 secs) is over
	PUSTime += DeltaTime;
	if (PUSTime > 5.f && PUActive == false)
	{
		PUActive = true;
		SpawnPowerUp();
	}
	
}

void APowerUpSpawner::SpawnPowerUp()
{
	//get location of spawner
	UWorld* World = GetWorld();

	FVector Location = GetActorLocation();
	if (WhichPU == 0) // spawn shotgun
	{
		AShotgun* Shotgun = World->SpawnActor<AShotgun>(ActorToSpawn, Location + FVector(0.f, 0.f, 0.f), GetActorRotation());
		if (Shotgun)
		{
			Shotgun->OnPUDestroyed.AddDynamic(this, &APowerUpSpawner::PowerUpDestroyed); //for broadcasting back to PUSpawner when PU destroyed
		}
	}
	else if (WhichPU == 1) //spawn healthpack
	{
		AHealthPack* HealthPack = World->SpawnActor<AHealthPack>(HealthToSpawn, Location + FVector(0.f, 0.f, 0.f), GetActorRotation());
		if (HealthPack)
		{
			HealthPack->OnHPDestroyed.AddDynamic(this, &APowerUpSpawner::HealthPackDestroyed);//for broadcasting back to PUSpawner when PU destroyed
		}
	}
	
}
// ran from Shotgun.cpp when shotgun object is destroyed
void APowerUpSpawner::PowerUpDestroyed()
{
	PUSTime = 0.f;
	WhichPU = 1;
	PUActive = false;
	UE_LOG(LogTemp, Warning, TEXT("Power-Up-cooldown started"));
}
// ran from HealthPack.cpp when shotgun object is destroyed
void APowerUpSpawner::HealthPackDestroyed()
{
	PUSTime = 0.f;
	WhichPU = 0;
	PUActive = false;
	UE_LOG(LogTemp, Warning, TEXT("Power-Up-cooldown started"));
}
