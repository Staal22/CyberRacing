// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class RACING_GAME_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    //called when hit, destroys actor
	void IsHit();

    FVector MoveDirection = FVector(1.f, 0.f, 0.f);


private:
    //Speed of enemy
    UPROPERTY(EditAnywhere, category="EnemyVariables")
        float Speed{ 150.f };

    //mnaximun turndelay (towards player)
    UPROPERTY(EditAnywhere, category = "EnemyVariables")
        float TurnDelayMax{ 5.f };

   //minimum turndelay (towards player)
    UPROPERTY(EditAnywhere, category = "EnemyVariables")
        float TurnDelayMin{ 1.f };

    float CurrentTurnDelay{ 0.f };

    //collider component
    UPROPERTY(EditAnywhere)
        class UShapeComponent* Root {nullptr};

    UPROPERTY(EditAnywhere)
        class UStaticMeshComponent* MeshComponent {nullptr};
};
