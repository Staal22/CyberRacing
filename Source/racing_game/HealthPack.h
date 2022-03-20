// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUpSpawner.h"
#include "racing_gameGameModeBase.h"
#include "HealthPack.generated.h"

//setting up delegate for casting to PlayerCar when collision with the healthpack is detected
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthPackHitPlayerSignature, AActor*, PlayerHit);
//setting up delegate for casting to PowerUpSpawner when the power up is destroyed
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHPDestroyedSignature);

UCLASS()
class RACING_GAME_API AHealthPack : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHealthPack();
	FHealthPackHitPlayerSignature OnHealthPackHitPlayer;
	FHPDestroyedSignature OnHPDestroyed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// setting up mesh component and collision component for healthpack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HPMesh")
		UStaticMeshComponent* HPMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HPThings")
		class USphereComponent* Collision{};

	//variables for turning and "bouncing" the healthpack
	float Speed = 50.f;
	bool bounceUp = true;
	float bounceTime = 0.f;
	float Turn = 0.f;

	// the function to be called when collision (overlap) is detected
	public:
		UFUNCTION()
			void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
				UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex,
				bool bFromSweep, const FHitResult& SweepResult);
	// the function to be called when the healthpack shall be destroyed
	UFUNCTION()
		void Destruction();

protected:
	UPROPERTY()
	Aracing_gameGameModeBase* RacingGameMode;
	
};