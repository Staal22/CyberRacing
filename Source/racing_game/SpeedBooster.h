
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpeedBooster.generated.h"

//setting up delegate for casting to PlayerCar when collision with the the speedbooster is detected
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpeedBoosterHitPlayerSignature, AActor*, PlayerHit);

UCLASS()
class RACING_GAME_API ASpeedBooster : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpeedBooster();
	FSpeedBoosterHitPlayerSignature OnSpeedBoosterHitPlayer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// setting up mesh component and collision component for speedbooster
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SBMesh")
		UStaticMeshComponent* SBMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SBThings")
		class UBoxComponent* Collision{};

public:
	// the function to be called when collision (overlap) is detected
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);
			
	UFUNCTION()
	float GetSpeedBoost();
			
private:
	UPROPERTY(EditAnywhere)
	float SpeedBoost = 2000.f;
};

