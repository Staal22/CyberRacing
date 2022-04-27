// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUpSpawner.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPUHitPlayerSignature, AActor*, BoxHit);

UCLASS()
class RACING_GAME_API APowerUpSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APowerUpSpawner();
	FPUHitPlayerSignature OnPUBoxHit;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	//setting up two actors that the PowerUpSpawner can spawn
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"));
	TSubclassOf<AActor> ActorToSpawn;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"));
	TSubclassOf<AActor> HealthToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PUSThings")
		class USphereComponent* Collision{};

	//setting up to functions to call when the shotgun or healthpack is destroyed
	UFUNCTION()
		void PowerUpDestroyed();

	UFUNCTION()
		void HealthPackDestroyed();

	// bool thats true if there is currently a powerup spawned
	bool PUActive = false;
	//variable for which power up was last spawned
	int WhichPU = 0;
	// float for cooldown to next power up to be spawned
	float PUSTime = 0.f;

	int randint;
	

	void SpawnPowerUp();

	void RandomPU();

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);
};

