// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBulletHitEnemySignature, AActor*, Enemyhit);


UCLASS()
class RACING_GAME_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

	FBulletHitEnemySignature OnBulletHitEnemy;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	UStaticMeshComponent* BulletMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	class USphereComponent* Collision = nullptr;
	
	UFUNCTION()
	void Death();
	
protected:


private:
	UPROPERTY(EditAnywhere, Category = "Bullet")
	float Speed = 6000.f;

	UPROPERTY(EditAnywhere, Category = "Bullet")
	float TimeToLive = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Bullet")
	float TimeLived = 0.0f;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
	
};
