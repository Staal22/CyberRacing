// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletEnemyTurret.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBulletHitEnemySignature, AActor*, Enemyhit);

UCLASS()
class RACING_GAME_API ABulletEnemyTurret : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ABulletEnemyTurret();
	FOnBulletHitEnemySignature OnBulletHitEnemy;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BulletEnemyTurret")
	class USphereComponent* Root = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BulletEnemyTurret")
	UStaticMeshComponent* BulletMesh = nullptr;
	
	UFUNCTION()
	void Death();
	

private:
	UPROPERTY(EditAnywhere, Category = "BulletEnemyTurret")
	float Speed = 6000.f;
	UPROPERTY(EditAnywhere, Category = "BulletEnemyTurret")
	float TimeToLive = 10.0f;
	UPROPERTY(EditAnywhere, Category = "BulletEnemyTurret")
	float TimeLived = 0.0f;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	//DeathFX, init through blueprint
	UPROPERTY(EditAnywhere, Category = "BulletEnemyTurretFX")
	UParticleSystem* ExplosionUponDeath = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "BulletEnemyTurretFX")
	USoundBase* DeathSound = nullptr;
};
