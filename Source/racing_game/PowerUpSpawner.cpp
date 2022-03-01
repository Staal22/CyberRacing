// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpSpawner.h"
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

	PUSTime += DeltaTime;
	if (PUSTime > 5.f && PUActive == false)
	{
		PUActive = true;
		SpawnPowerUp();
	}
	
}

void APowerUpSpawner::SpawnPowerUp()
{
	UWorld* World = GetWorld();

	FVector Location = GetActorLocation();

	AShotgun* Shotgun = World->SpawnActor<AShotgun>(ActorToSpawn, Location + FVector(0.f, 0.f, 0.f), GetActorRotation());
	Shotgun->OnPUDestroyed.AddDynamic(this, &APowerUpSpawner::PowerUpDestroyed);
}

void APowerUpSpawner::PowerUpDestroyed()
{
	PUSTime = 0.f;
	PUActive = false;
	UE_LOG(LogTemp, Warning, TEXT("Power-Up-cooldown started"));
}
