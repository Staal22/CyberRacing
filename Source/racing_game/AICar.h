// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayerCar.h"
#include "SplineClass.h"
#include "AICar.generated.h"

UCLASS()
class RACING_GAME_API AAICar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAICar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// setting up mesh component and collision component for coin
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AICarMesh")
		UStaticMeshComponent* AICarMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AICarThings")
		class USphereComponent* Collision{};

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"));
	TSubclassOf<AActor> MineSpawn;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"));
	TSubclassOf<AActor> MissileSpawn;

	FVector CarDirection = FVector(0.f, 0.f, 0.f);

	UFUNCTION(BlueprintImplementableEvent)
	void NiagaraBoost();
	
	void LineTrace();
	void SpeedBoost();

	UFUNCTION(BlueprintCallable)
	void Missile();
	void MissilePU();
	void MinePU();
	void PUActive();
	void MissileFlip();
	void MineFlip();

	float randInt;
	float randInt2;
	bool PUAct = false;
	bool ColCheck = true;
	bool MHit = false;
	bool MisPU = false;
	bool MiPU = false;
	bool Count = true;
	float HoverHeight = 250;
	float WallCheck = 3500;
	float WallCheck2 = 500;
	float InterpSpeed = 200.f;
	float InterpSpeed2 = 0.05f;
	FVector Ruler;
	FVector RulerRight;
	FVector RulerLeft;
	FVector WallImpact;
	FVector Forward;
	FVector Up;
	FRotator SmoothRot;
	FRotator ROTTOT;
	FRotator MyRotator;
	FRotator MyRotator2;
	FRotator MyRotator3;
	FRotator MyRotator4;
	FRotator LastRotation;
	FHitResult OutHit1;
	FHitResult OutHit2;
	FString Name = TEXT("racetrack_rework");
	FString NameCheck;

	float AngleAxis;

	float RotationCheck;
	float Time;
	float BoostTime = 5.f;
	float Turn = 0.f;
	float Speed = 3;
	float PUTime = 0.f;

private:

	UPROPERTY(EditAnywhere)
		float ForceStrength;

	UPROPERTY(EditAnywhere)
		float ForceStrength2;
	
	UPROPERTY()
		class Aracing_gameGameModeBase* RacingGameMode;

	UPROPERTY()
		class ACoin* Coin;

	UPROPERTY()
		class AShotgun* Shotgun;

	UPROPERTY()
		class AEnemy* Enemy;

	UPROPERTY()
		class AEnemyC* EnemyC;

	UPROPERTY()
		class AHealthPack* HP;

	UPROPERTY()
		class URacingGameInstance* RacingGameInstance;
};
