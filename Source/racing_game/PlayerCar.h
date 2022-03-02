// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCar.generated.h"

UCLASS()
class RACING_GAME_API APlayerCar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCar")
	//UArrowComponent* Arrow = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCar")
	class UStaticMeshComponent* PlayerMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UFloatingPawnMovement* PawnMovementComponent = nullptr;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"));
	TSubclassOf<AActor> BulletToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCar")
	class UCameraComponent* Camera = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCar")
	class USpringArmComponent* SpringArm = nullptr;

	UFUNCTION()
	void Drive(float Force);

	UFUNCTION()
	void Turn(float TurnDirection);

	UFUNCTION()
	void OnEnemyHit(AActor* Actor);

	UFUNCTION()
	void Shoot();

	UFUNCTION()
	void ShotgunPU();

	UFUNCTION()
	void Reload();

	UFUNCTION()
	float GetAmmo();

	UFUNCTION()
	float GetMaxAmmo();

protected:
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* AmmoComp;

private:
	//UPROPERTY()
	//float MoveSpeed = 15.f;

	UPROPERTY()
	bool bShotgun = false;

	UPROPERTY()
	class Aracing_gameGameModeBase* RacingGameMode;

	UPROPERTY()
	float TurnSpeed = 2.f;

	UPROPERTY()
	int Ammo = 0;

	UPROPERTY()
	int MaxAmmo = 20;

	UPROPERTY()
	class UAmmoCounter* AmmoCounter;

	UPROPERTY()
	class ABullet* Bullet;

	//UPROPERTY()
	//TArray<class ABullet*> Bullets;

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;

};
