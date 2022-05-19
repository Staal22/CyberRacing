// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
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
	class USphereComponent* Sphere = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "PlayerCar")
	UStaticMeshComponent* PlayerMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "PlayerCar")
	UArrowComponent* WallArrow = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "PlayerCar")
	UArrowComponent* VfxArrow1 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "PlayerCar")
	UArrowComponent* VfxArrow2 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "PlayerCar")
	UArrowComponent* VfxArrow3 = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UFloatingPawnMovement* PawnMovementComponent = nullptr;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"));
	TSubclassOf<AActor> LaserToSpawn;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"));
	TSubclassOf<AActor> MissileToSpawn;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"));
	TSubclassOf<AActor> PVPMissileToSpawn;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"));
	TSubclassOf<AActor> MineToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "PlayerCar")
	class UCameraComponent* Camera = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "PlayerCar")
	UCameraComponent* Back_Camera = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "PlayerCar")
	UCameraComponent* Top_Camera = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "PlayerCar")
	class USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "PlayerCar")
	USpringArmComponent* Back_SpringArm = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "PlayerCar")
	USpringArmComponent* Top_SpringArm = nullptr;

	UPROPERTY(EditAnywhere, Category = "PlayerCar")
	USoundBase* ShootingSound = nullptr;

	UPROPERTY(EditAnywhere, Category = "PlayerCar")
	USoundBase* ReloadingSound = nullptr;
	
	UPROPERTY()
	FString RoadTest = "";
	
	UFUNCTION()
	void Drive(float Force);

	UFUNCTION()
	void WallCheck();

	UFUNCTION()
	void Turn(float TurnDirection);

	UFUNCTION()
	void OnEnemyHit(AActor* Actor);

	UFUNCTION()
	void ShootLaser();
	
	UFUNCTION(BlueprintImplementableEvent)
	void Pause();

	UFUNCTION(BlueprintCallable)
	void Lap();
	
	// UFUNCTION()
	// void ShootMissile();
	
	UFUNCTION(BlueprintImplementableEvent)
	void Checkpoint();

	UFUNCTION()
	int GetPU();

	UFUNCTION()
	bool ShotgunActive();
	
	UFUNCTION()
	void CoinAcquired();

	UFUNCTION(BlueprintImplementableEvent)
	void NiagaraBoost();
	
	UFUNCTION()
	void ShotgunPU();

	UFUNCTION()
	void MinePU();

	UFUNCTION()
	void MissilePU();

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
	void SetSpeedBoost(float InBoost);

	UFUNCTION()
	void SetSpeedBoostDirection(FVector InVector);

	UFUNCTION()
	void BackCamOn();

	UFUNCTION()
	void BackCamOff();
	
	UFUNCTION(BlueprintCallable)
	void HitByMissile();
	
	UFUNCTION()
	void ToggleTopCam();
	
	UFUNCTION(BlueprintCallable)
	float GetTAtkTime();

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> AmmoWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LapCounterWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> SpeedWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HealthWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> PUDisplayClass;

	// UPROPERTY(EditAnywhere)
	// TSubclassOf<UPhysicalMaterial> WallPhysMaterialClass;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HPComp;
	
	UPROPERTY(VisibleAnywhere)
	class UAmmoCounter* AmmoCounter;

	UPROPERTY(VisibleAnywhere)
	class ULapCounter* LapCounter;
	
	UPROPERTY(VisibleAnywhere)
	class UPowerUpDisplay* PowerUpDisplay;
	
	UPROPERTY(VisibleAnywhere)
	class USpeedometer* Speedometer;

	UPROPERTY(VisibleAnywhere)
	class UHealthBar* HealthBar;

	UPROPERTY(VisibleAnywhere)
	UHealthBar* FollowHealthBar;

	// UPROPERTY(VisibleAnywhere)
	// class UPhysicalMaterial* WallPhysMaterial;
	
	UPROPERTY(BlueprintReadWrite, Category= "PlayerCar")
	float InitTAtkTime = 15.f;
	
	UPROPERTY(BlueprintReadWrite, Category= "PlayerCar")
	int Checkpoints = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "PlayerCar")
	float HoverForce;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "PlayerCar")
	float TurnForce;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "PlayerCar")
	float TraceLength;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "PlayerCar")
	float GravityForce;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "PlayerCar")
	bool bDoARoll = false;

	UPROPERTY(BlueprintReadOnly)
	bool bHitState = false;
	
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
	bool bShotgun = false;

	UPROPERTY()
	bool bMissile = false;

	UPROPERTY()
	bool bMine = false;
	
	UPROPERTY()
	bool bTopCam = false;

	UPROPERTY()
	float HitTimer = 0.f;
	
	UPROPERTY()
	bool bIsReloading = false;
	
	UPROPERTY()
	int Ammo = 0;
	
	UPROPERTY()
	float TAtkTime = 0.f;
	
	UPROPERTY()
	float SpeedBoost = 0.f;

	UPROPERTY()
	FVector SpeedBoostDirection;
	
	UPROPERTY()
	int MaxAmmo = 20;

	UPROPERTY()
	int Health = 0;

	UPROPERTY()
	int MaxHealth = 3;
	
	UPROPERTY()
	float ToRoll;
	
	UPROPERTY()
	float TimeSinceDamage = 0.f;

	UPROPERTY()
	float TimeSinceRoll = 0.f;

	UPROPERTY()
	float TimeSinceBounce = 0.f;

	UPROPERTY()
	float Timer = 0.f;

	UPROPERTY()
	float MaxMoveSpeed = 6000.f;

	UPROPERTY()
	float DefaultTraceLength = 400.f;

	UPROPERTY()
	float DefaultTurnForce = 40000.f;

	UPROPERTY()
	float DefaultHoverForce = 1400000.f;

	UPROPERTY()
	float DefaultGravityForce = -120000.f;
	
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
	float AileronDuration = 1.f;

	UPROPERTY()
	float Target = 180.f;
	
	UPROPERTY()
	class Aracing_gameGameModeBase* RacingGameMode;

	UPROPERTY()
	class URacingGameInstance* RacingGameInstance;
	
	UPROPERTY()
	class ABullet* Bullet;

	// UPROPERTY()
	// TArray<class ABullet*> Bullets;

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
	
	FTimerHandle TimerHandleSpeed;
	FTimerDelegate TimerDelegateSpeed;
	
	FTimerHandle TimerHandleRoll;
	FTimerDelegate TimerDelegateRoll;

	FTimerHandle TimerHandleReload;
	FTimerDelegate TimerDelegateReload;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
	
};
