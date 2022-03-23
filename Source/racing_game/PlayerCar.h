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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "PlayerCar")
	class USphereComponent * Sphere = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "PlayerCar")
	UStaticMeshComponent* PlayerMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UFloatingPawnMovement* PawnMovementComponent = nullptr;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"));
	TSubclassOf<AActor> BulletToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "PlayerCar")
	class UCameraComponent* Camera = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "PlayerCar")
	class USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(EditAnywhere, Category = "PlayerCar")
	USoundBase* ShootingSound = nullptr;

	UPROPERTY(EditAnywhere, Category = "PlayerCar")
	USoundBase* ReloadingSound = nullptr;
	
	UPROPERTY()
	FString RoadTest = "";
	
	UFUNCTION()
	void Drive(float Force);

	UFUNCTION()
	void Turn(float TurnDirection);

	UFUNCTION()
	void OnEnemyHit(AActor* Actor);

	UFUNCTION()
	void Shoot();
	
	UFUNCTION(BlueprintImplementableEvent)
	void Checkpoint();

	UFUNCTION()
	void ShotgunPU();

	UFUNCTION()
	void SpeedPU();

	UFUNCTION()
	void Reload();

	UFUNCTION()
	void AileronRoll();

	UFUNCTION()
	int GetAmmo();
	
	UFUNCTION()
	int GetMaxAmmo();

	UFUNCTION()
	int GetHealth();

	UFUNCTION()
	int GetMaxHealth();

	UFUNCTION()
	void HealthPack();

	UFUNCTION()
	void SpeedLimit();
	
	UFUNCTION()
	float GetSpeed();

	UFUNCTION()
	void BoostOn();

	UFUNCTION()
	void BoostOff();

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> AmmoWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> SpeedWidgetClass;

	// UPROPERTY(EditAnywhere)
	// TSubclassOf<UUserWidget> HealthWidgetClass;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HPComp;
	
	UPROPERTY(VisibleAnywhere)
	class UAmmoCounter* AmmoCounter;

	UPROPERTY(VisibleAnywhere)
	class USpeedometer* Speedometer;

	UPROPERTY(VisibleAnywhere)
	class UHealthBar* HealthBar;
	
	UPROPERTY(BlueprintReadWrite, Category= "PlayerCar")
	int Checkpoints = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "PlayerCar")
	float HoverForce;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "PlayerCar")
	float TraceLength;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "PlayerCar")
	bool bDoARoll = false;
	
	// UPROPERTY(VisibleAnywhere)
	// class UWidgetComponent* AmmoComp;
	//
	// UPROPERTY(VisibleAnywhere)
	// UWidgetComponent* ScoreComp;
	//
	// UPROPERTY(VisibleAnywhere)
	// UWidgetComponent* SpeedComp;

private:
	UPROPERTY()
	FString CommandString = "";
	
	UPROPERTY()
	FVector Forward;

	UPROPERTY()
	FRotator Rotation;

	UPROPERTY()
	FVector Velocity;

	UPROPERTY()
	float ToRoll;
	
	UPROPERTY()
	float TimeSinceEvent = 0.f;

	UPROPERTY()
	float Timer = 0.f;
	
	UPROPERTY()
	float MaxMoveSpeed = 3400.f;

	UPROPERTY()
	float DefaultTraceLength = 250.f;

	UPROPERTY()
	float DefaultHoverForce = 700000.f;
	
	UPROPERTY()
	float MoveForce = 0.f;

	UPROPERTY()
	float Speed = 0.f;

	UPROPERTY()
	float CameraPos = 0.f;

	UPROPERTY()
	float PitchRadian = 0.f;

	UPROPERTY()
	float TurnSpeed = 0.f;

	UPROPERTY()
	float TimeElapsed = 0.f;

	UPROPERTY()
	float AileronDuration = 1.f;

	UPROPERTY()
	float Target = 180.f;

	UPROPERTY()
	bool bShotgun = false;
	
	UPROPERTY()
	class Aracing_gameGameModeBase* RacingGameMode;

	UPROPERTY()
	int Ammo = 0;

	UPROPERTY()
	int MaxAmmo = 20;

	UPROPERTY()
	int Health = 0;

	UPROPERTY()
	int MaxHealth = 3;

	UPROPERTY()
	class ABullet* Bullet;

	// UPROPERTY()
	// TArray<class ABullet*> Bullets;

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
	
};
