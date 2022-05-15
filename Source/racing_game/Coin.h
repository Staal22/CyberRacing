// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

//setting up delegate for casting to PlayerCar when collision with the coin is detected
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCoinHitPlayerSignature, AActor*, PlayerHit);

UCLASS()
class RACING_GAME_API ACoin : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACoin();
	FCoinHitPlayerSignature OnCoinHitPlayer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// setting up mesh component and collision component for coin
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoinMesh")
		UStaticMeshComponent* CoinMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoinThings")
		class USphereComponent* Collision{};

	// a float purposed for how many degrees the coin has turned
	float Turn = 0.f;

public:
	UPROPERTY(EditAnywhere)
	USoundBase* PickUpSound = nullptr;
	
	// the function to be called when collision (overlap) is detected
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY()
	class Aracing_gameGameModeBase* RacingGameMode;

	UPROPERTY()
	class APlayerCar* PlayerCar;
	
};

