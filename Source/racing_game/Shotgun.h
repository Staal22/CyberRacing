// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUpSpawner.h"
#include "Shotgun.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPowerUpHitPlayerSignature, AActor*, PlayerHit);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPUDestroyedSignature);

UCLASS()
class RACING_GAME_API AShotgun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShotgun();
	FPowerUpHitPlayerSignature OnPowerUpHitPlayer;
	FPUDestroyedSignature OnPUDestroyed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShotgunMesh")
		UStaticMeshComponent* ShotgunMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShotgunThings")
		class USphereComponent* Collision{};

	float Speed = 50.f;
	bool bounceUp = true;
	float bounceTime = 0.f;
	float Turn = 0.f;

public:
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void Destruction();

};
