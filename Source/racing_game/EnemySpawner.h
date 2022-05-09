// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class RACING_GAME_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"));
	TSubclassOf<AActor> ActorToSpawn;


	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// bool thats true if there is currently an enemy spawned
	bool EnemyActive = false;
	//variable for which enemy was last spawned
	int WhichEnemy = 0;
	// float for cooldown for enemy to be spawned
	float EnemyTime = 0.f;
	
	void SpawnEnemy();

	UFUNCTION()
	void EnemyDestroyed();



};
