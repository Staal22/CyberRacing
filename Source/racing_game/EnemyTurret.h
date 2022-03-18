// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.h"
#include "EnemyTurret.generated.h"


UCLASS()
class RACING_GAME_API AEnemyTurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets default values for this actor's properties
	AEnemyTurret();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USkeletalMeshComponent* SkeletalMesh{ nullptr };

	//called when hit, destroys actor
	void IsHit();

	void Shoot();

	UPROPERTY()
	FVector RotationDirection = FVector(1.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"));
	TSubclassOf<AActor> BulletToSpawn;

private:
	
	//collider component
	UPROPERTY(EditAnywhere)
		class UShapeComponent* Root{ nullptr };
	
	//DeathFX, init through blueprint
	UPROPERTY(EditAnywhere, Category = "EnemyFX")
		UParticleSystem* ExplosionUponDeath = nullptr;
	
	//DeathFX, init through blueprint
	UPROPERTY(EditAnywhere, Category = "EnemyFX")
		USoundBase* DeathSound = nullptr;

	//bullet
	UPROPERTY()
		class ABullet* Bullet;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
