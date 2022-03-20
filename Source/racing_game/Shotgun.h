// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUpSpawner.h"
#include "Shotgun.generated.h"

//setting up delegate for casting to PlayerCar when collision with the shotgun is detected
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPowerUpHitPlayerSignature, AActor*, PlayerHit);
//setting up delegate for casting to PowerUpSpawner when the power up is destroyed
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
	// setting up mesh component and collision component for shotgun
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShotgunMesh")
		UStaticMeshComponent* ShotgunMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShotgunThings")
		class USphereComponent* Collision{};

	//variables for turning and "bouncing" the shotgun
	float Speed = 50.f;
	bool bounceUp = true;
	float bounceTime = 0.f;
	float Turn = 0.f;

public:
	// the function to be called when collision (overlap) is detected
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);
	// the function to be called when the shotgu shall be destroyed
	UFUNCTION()
	void Destruction();

};
