// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletEnemyTurret.generated.h"


//setting up delegate for casting to PlayerCar when collision with the bullet is detected
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBulletHitEnemySignature, AActor*, Enemyhit);

UCLASS()
class RACING_GAME_API ABulletEnemyTurret : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ABulletEnemyTurret();
	//Delegate
	FOnBulletHitEnemySignature OnBulletHitEnemy;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Simple box collision
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BulletEnemyTurret")
	class USphereComponent* Root = nullptr;

	//Static mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BulletEnemyTurret")
	UStaticMeshComponent* BulletMesh = nullptr;

	//Called when bullet collides with player or other mesh
	UFUNCTION()
	void Death();

private:
	//Speed
	UPROPERTY(EditAnywhere, Category = "BulletEnemyTurret")
	float Speed = 6000.f;
	//Maximum duration bullet travels before death/removal of actor is called
	UPROPERTY(EditAnywhere, Category = "BulletEnemyTurret")
	float TimeToLive = 10.0f;
	//Tracks the time the bullet has existed in the world
	UPROPERTY(EditAnywhere, Category = "BulletEnemyTurret")
	float TimeLived = 0.0f;
	//Collision detection
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	//DeathFX, init through blueprint:
	//Particle FX
	UPROPERTY(EditAnywhere, Category = "BulletEnemyTurretFX")
	UParticleSystem* ExplosionUponDeath = nullptr;
	//DeathSound
	UPROPERTY(EditAnywhere, Category = "BulletEnemyTurretFX")
	USoundBase* DeathSound = nullptr;
};
