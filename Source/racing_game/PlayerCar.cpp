// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCar.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include <Components/WidgetComponent.h>
#include "AmmoCounter.h"
#include <Kismet/GameplayStatics.h>
#include "Bullet.h"
#include "Enemy.h"
#include "racing_gameGameModeBase.h"
#include "ScoreCounter.h"
#include "Speedometer.h"
#include "Components/SphereComponent.h"
// #include "DrawDebugHelpers.h"

// Sets default values
APlayerCar::APlayerCar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	PlayerMesh->SetupAttachment(GetRootComponent());
	// SetRootComponent(PlayerMesh);

	PawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMoveComp"));
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetUsingAbsoluteRotation(false);
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 800;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 20.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	// AmmoComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	// AmmoComp->SetupAttachment(GetRootComponent());
	Ammo = MaxAmmo;

	// ScoreComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("ScoreCounter"));
	// ScoreComp->SetupAttachment(GetRootComponent());
	//
	// SpeedComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Speedometer"));
	// SpeedComp->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void APlayerCar::BeginPlay()
{
	Super::BeginPlay();
	
	//Forward = GetActorForwardVector();
	UWorld* World = GetWorld();
	RacingGameMode = Cast<Aracing_gameGameModeBase>(GetWorld()->GetAuthGameMode());

	if (IsValid(AmmoWidgetClass))
		AmmoCounter = Cast<UAmmoCounter>(CreateWidget(World, AmmoWidgetClass));
	AmmoCounter->SetOwner(this);
	AmmoCounter->SetDesiredSizeInViewport(FVector2D(360.f, 40.f));
	AmmoCounter->SetPositionInViewport(FVector2D(0.f, 40.f));
	AmmoCounter->AddToViewport();
	AmmoCounter->AmmoUpdate();

	if (IsValid(ScoreWidgetClass))
		ScoreCounter = Cast<UScoreCounter>(CreateWidget(World, ScoreWidgetClass));
	ScoreCounter->SetOwner(this);
	ScoreCounter->SetDesiredSizeInViewport(FVector2D(100.f, 40.f));
	ScoreCounter->SetPositionInViewport(FVector2D(0.f, 0.f));
	ScoreCounter->AddToViewport();
	ScoreCounter->ScoreUpdate();

	if (IsValid(SpeedWidgetClass))
		Speedometer = Cast<USpeedometer>(CreateWidget(World, SpeedWidgetClass));
	Speedometer->SetOwner(this);
	Speedometer->SetDesiredSizeInViewport(FVector2D(270.f, 40.f));
	Speedometer->SetPositionInViewport(FVector2D(0.f, 80.f));
	Speedometer->AddToViewport();
	Speedometer->SpeedUpdate();
	
	// AmmoCounter = Cast<UAmmoCounter>(AmmoComp->GetUserWidgetObject());
	// ScoreCounter = Cast<UScoreCounter>(ScoreComp->GetUserWidgetObject());
	// Speedometer = Cast<USpeedometer>(SpeedComp->GetUserWidgetObject());
	
}

// Called every frame
void APlayerCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UWorld* World = GetWorld();
	FRotator Rotation = PlayerMesh->GetRelativeRotation();
	Speed = FMath::Clamp(PawnMovementComponent->Velocity.Size(), 0.f, 2400.f) / PawnMovementComponent->MaxSpeed;
	
	SpringArm->SetRelativeLocation(FVector(CameraPos, 0.f, 0.f));

	Speedometer->SpeedUpdate();
	
	if (FMath::IsNearlyEqual(Rotation.Roll, -10.f, 9.f))
	{
		bDoARoll = false;
		PlayerMesh->SetRelativeRotation(FRotator(Rotation.Pitch, Rotation.Yaw, 0.f));
	}
	
	if (MoveForce > 0.f)
	{
		CameraPos = Speed * 350.f;
		PawnMovementComponent->MaxSpeed = 2400;
		PawnMovementComponent->Acceleration = 400;
	}
	else if (MoveForce < 0.f)
	{
		CameraPos = 100.f;
		PawnMovementComponent->MaxSpeed = 1200;
		PawnMovementComponent->Acceleration = 600;
	}
	AddMovementInput(Sphere->GetForwardVector(), MoveForce);

	Sphere->AddTorqueInRadians(GetActorUpVector() * TurnSpeed * 75000);
	
	if (bDoARoll == true)
	{
		PlayerMesh->SetRelativeRotation(FMath::RInterpTo(Rotation, FRotator(Rotation.Pitch, Rotation.Yaw, Rotation.Roll + 13.f), DeltaTime, 40.f));
		// TimeElapsed += DeltaTime;
	}
	
	if (MoveForce > 0.f)
	{
		if (PlayerMesh->GetRelativeRotation().Pitch > -7.f)
		{
			// PlayerMesh->AddTorqueInRadians(GetActorRightVector() * PitchRadian * 3000);
			PlayerMesh->AddRelativeRotation(FRotator(-0.1f, 0.f, 0.f));
		}
	}
	else if (MoveForce < 0.f)
	{
		if (PlayerMesh->GetRelativeRotation().Pitch < 10.f)
		{
			// PlayerMesh->AddTorqueInRadians(GetActorRightVector() * PitchRadian * 6000);
			PlayerMesh->AddRelativeRotation(FRotator(0.1f, 0.f, 0.f));
		}
	}
		
}

// Called to bind functionality to input
void APlayerCar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &APlayerCar::Drive);
	PlayerInputComponent->BindAxis("TurnL", this, &APlayerCar::Turn);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerCar::Shoot);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &APlayerCar::Reload);
	PlayerInputComponent->BindAction("AileronRoll", IE_Pressed, this, &APlayerCar::AileronRoll);
	PlayerInputComponent->BindAction("Boost", IE_Pressed, this, &APlayerCar::BoostOn);
	PlayerInputComponent->BindAction("Boost", IE_Released, this, &APlayerCar::BoostOff);
}

void APlayerCar::Drive(float Force)
{
	MoveForce = Force;
	PitchRadian = Force;
}

void APlayerCar::Turn(float TurnDirection)
{
	TurnSpeed = TurnDirection;
}

void APlayerCar::OnEnemyHit(AActor* Actor)
{
	if (Actor->IsA<AEnemy>())
	{
		Cast<AEnemy>(Actor)->IsHit();
		if (RacingGameMode)
		{
			RacingGameMode->EnemyDied();
		}
		ScoreCounter->ScoreUpdate();
	}

	UE_LOG(LogTemp, Warning, TEXT("Enemy killed"));
}

void APlayerCar::Shoot()
{
	if (Ammo <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, FString::Printf(TEXT("No ammo. Reload")));

	}
	if (Ammo > 0)
	{
		UWorld* World = GetWorld();
		FVector Location = GetActorLocation();
		if (bShotgun == true)
		{
			TArray<ABullet*> Bullets;
			Ammo -= 3;
			if (Ammo < 0)
			{
				Ammo = 0;
			}
			//implement TArray of actors and so on
			Bullets.Emplace(World->SpawnActor<ABullet>(BulletToSpawn, Location + GetActorForwardVector() * 100.f + GetActorRightVector() * -50.f, GetActorRotation()));
			Bullets.Emplace(World->SpawnActor<ABullet>(BulletToSpawn, Location + GetActorForwardVector() * 100.f, GetActorRotation()));
			Bullets.Emplace(World->SpawnActor<ABullet>(BulletToSpawn, Location + GetActorForwardVector() * 100.f + GetActorRightVector() * 50.f, GetActorRotation()));
			for (int i = 0; i < 3; i++)
			{
				Cast<ABullet>(Bullets[i])->OnBulletHitEnemy.AddDynamic(this, &APlayerCar::OnEnemyHit);
			}
		}
		else
		{
			Ammo--;
			if (World)
			{
				Bullet = World->SpawnActor<ABullet>(BulletToSpawn, Location + GetActorForwardVector() * 100.f, GetActorRotation());
				//UGameplayStatics::PlaySound2D(World, ShootingSound, 1.0f, 1.0f, 0.0f, 0);
				if (Bullet)
				{
					Bullet->OnBulletHitEnemy.AddDynamic(this, &APlayerCar::OnEnemyHit);
				}
			}
		}
	}
	AmmoCounter->AmmoUpdate();
	UE_LOG(LogTemp, Warning, TEXT("Shooting"));

}

void APlayerCar::ShotgunPU()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("SHOTGUN")));
	bShotgun = true;
}

void APlayerCar::Reload()
{
	// UWorld* World = GetWorld();
	//UGameplayStatics::PlaySound2D(World, ReloadingSound, 1.f, 1.f, 0.f, 0);
	GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Yellow, FString::Printf(TEXT("Reloading... (takes 1 second)")));
	
	TimerDelegate.BindLambda([&]
		{
			Ammo = 20;
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Reloaded")));
			AmmoCounter->AmmoUpdate();
		});

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 1, false);

}

void APlayerCar::AileronRoll()
{
	bDoARoll = true;
}

float APlayerCar::GetAmmo()
{
	return Ammo;
}

float APlayerCar::GetMaxAmmo()
{
	return MaxAmmo;
}

float APlayerCar::GetSpeed()
{
	if (MoveForce < 0.f)
	{
		return 0.f;
	}
	return Speed;
}

void APlayerCar::BoostOn()
{

}

void APlayerCar::BoostOff()
{

}

