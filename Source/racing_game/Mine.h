// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Mine.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMineHitCarSignature, AActor*, CarHit);

UCLASS()
class RACING_GAME_API AMine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMine();
	//FMineHitCarSignature OnMineHitCar;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MineMesh")
		UStaticMeshComponent* MineMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MineThings")
		class USphereComponent* Collision{};

	UPROPERTY(EditAnywhere, Category = "MineFX")
		UParticleSystem* MineExplosion = nullptr;

	UPROPERTY()
		class AAICar* AICar;

	UPROPERTY()
		class APlayerCar* PlayerCar;


	UFUNCTION()
		void Explosion();

	/*UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);*/

	UPROPERTY()
		TArray<AActor*> Result;
	
	float BombTime = 0;
	float ActTime = 0;
	bool HitCar = false;

};
