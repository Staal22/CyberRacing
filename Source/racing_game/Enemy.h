// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

//setting up delegate for casting to EnemySpawner when the power up is destroyed
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPUOnEnemyDestruction);

UCLASS()
class RACING_GAME_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();
    //Delegate for destruction event
    FPUOnEnemyDestruction OnEnemyDestruction;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    //called when hit, destroys actor
	void IsHit();
    FVector MoveDirection = FVector(1.f, 0.f, 0.f);

    //collider component
    UPROPERTY(EditAnywhere)
        class UShapeComponent* Root {nullptr};

    //skeletal mesh
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        class USkeletalMeshComponent* SkeletalMesh {nullptr};

private:
    //MovementSpeed of enemy
    UPROPERTY(EditAnywhere, category="EnemyVariables")
        float Speed{ 5.f };

    //mnaximun turndelay (towards player)
    UPROPERTY(EditAnywhere, category = "EnemyVariables")
        float TurnDelayMax{ 5.f };

   //minimum turndelay (towards player)
    UPROPERTY(EditAnywhere, category = "EnemyVariables")
        float TurnDelayMin{ 1.f };

    UPROPERTY(EditAnywhere, category = "EnemyVariables")
    float CurrentTurnDelay{ 0.f };
    
    //DeathFX, init through blueprint
    //Particle FX
    UPROPERTY(EditAnywhere, Category = "EnemyFX")
        UParticleSystem* ExplosionUponDeath = nullptr;

    //DeathSound
    UPROPERTY(EditAnywhere, Category = "EnemyFX")
        USoundBase* DeathSound = nullptr;

    //AI controller
    UPROPERTY(EditAnywhere, Category = "EnemyAIController")
        class AAIController* AIController = nullptr;
   
};
