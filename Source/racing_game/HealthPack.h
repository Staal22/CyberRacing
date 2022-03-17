// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUpSpawner.h"
#include "racing_gameGameModeBase.h"
#include "HealthPack.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthPackHitPlayerSignature, AActor*, PlayerHit);

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HPMesh")
		UStaticMeshComponent* HPMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HPThings")
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

protected:
	UPROPERTY()
	Aracing_gameGameModeBase* RacingGameMode;
	
};