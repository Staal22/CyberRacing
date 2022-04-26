// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCar.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"
#include "AmmoCounter.h"
#include <Kismet/GameplayStatics.h>
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyC.h"
#include "HealthBar.h"
#include "RacingGameInstance.h"
#include "racing_gameGameModeBase.h"
#include "Speedometer.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
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
	SpringArm->SetRelativeRotation(FRotator(-10.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 1200;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 20.f;

	Back_SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("BackSpringArmComp"));
	Back_SpringArm->bDoCollisionTest = false;
	Back_SpringArm->SetUsingAbsoluteRotation(false);
	Back_SpringArm->SetupAttachment(GetRootComponent());
	Back_SpringArm->SetRelativeLocation(FVector(-350.f, 0.f, 0.f));
	Back_SpringArm->SetRelativeRotation(FRotator(-15.f, 180.f, 0.f));
	Back_SpringArm->TargetArmLength = 800;
	Back_SpringArm->bEnableCameraLag = false;

	Top_SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("TopSpringArmComp"));
	Top_SpringArm->bDoCollisionTest = false;
	Top_SpringArm->SetUsingAbsoluteRotation(false);
	Top_SpringArm->SetupAttachment(GetRootComponent());
	Top_SpringArm->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	Top_SpringArm->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	Top_SpringArm->TargetArmLength = 5000;
	Top_SpringArm->bEnableCameraLag = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	Back_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("BackCamera"));
	Back_Camera->bUsePawnControlRotation = false;
	Back_Camera->SetupAttachment(Back_SpringArm, USpringArmComponent::SocketName);

	Top_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopCamera"));
	Top_Camera->bUsePawnControlRotation = false;
	Top_Camera->SetupAttachment(Top_SpringArm, USpringArmComponent::SocketName);

	HPComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("FollowHealthBar"));
	HPComp->SetupAttachment(GetRootComponent());
	
	Ammo = MaxAmmo;
	Health = MaxHealth;
}

// Called when the game starts or when spawned
void APlayerCar::BeginPlay()
{
	Super::BeginPlay();
	
	//Forward = GetActorForwardVector();
	const auto World = GetWorld();
	RacingGameMode = Cast<Aracing_gameGameModeBase>(GetWorld()->GetAuthGameMode());
	RacingGameInstance = Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(World));
	
	if (IsValid(AmmoWidgetClass))
		AmmoCounter = Cast<UAmmoCounter>(CreateWidget(World, AmmoWidgetClass));
	AmmoCounter->SetOwner(this);
	AmmoCounter->SetDesiredSizeInViewport(FVector2D(360.f, 40.f));
	AmmoCounter->SetPositionInViewport(FVector2D(0.f, 40.f));
	AmmoCounter->AddToViewport();
	AmmoCounter->AmmoUpdate();

	if (IsValid(SpeedWidgetClass))
		Speedometer = Cast<USpeedometer>(CreateWidget(World, SpeedWidgetClass));
	Speedometer->SetOwner(this);
	Speedometer->SetDesiredSizeInViewport(FVector2D(270.f, 40.f));
	Speedometer->SetPositionInViewport(FVector2D(0.f, 80.f));
	Speedometer->AddToViewport();
	Speedometer->SpeedUpdate();
	
	if (IsValid(HealthWidgetClass))
		HealthBar = Cast<UHealthBar>(CreateWidget(World, HealthWidgetClass));
	HealthBar->SetOwner(this);
	HealthBar->SetDesiredSizeInViewport(FVector2D(270.f, 40.f));
	HealthBar->SetPositionInViewport(FVector2D(0.f, 120.f));
	HealthBar->HealthUpdate();
	
	FollowHealthBar = Cast<UHealthBar>(HPComp->GetUserWidgetObject());
	FollowHealthBar->SetOwner(this);
	FollowHealthBar->HealthUpdate();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &APlayerCar::OnOverlap);
	
	HoverForce = DefaultHoverForce;
	TraceLength = DefaultTraceLength;
	GravityForce = DefaultGravityForce;

	Back_Camera->Deactivate();

	InitTAtkTime = RacingGameMode->GetDifficulty( "Timer");
	TAtkTime = InitTAtkTime;
}

// Called every frame
void APlayerCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto World = GetWorld();
	Rotation = PlayerMesh->GetRelativeRotation();
	Forward = PlayerMesh->GetForwardVector();
	Velocity = PawnMovementComponent->Velocity;
	Speed = FMath::Clamp(Velocity.Size(), 0.f, PawnMovementComponent->MaxSpeed) / PawnMovementComponent->MaxSpeed;

	if (RacingGameInstance->GetTimeAtkActive())
	{
		TAtkTime = InitTAtkTime - World->GetTimeSeconds();
		if (TAtkTime <= 0.f)
		{
			RacingGameMode->GameOver( "Ran out of time" );
		}
	}
	
	SpringArm->SetRelativeLocation(FVector(CameraPos, 0.f, 0.f));

	Speedometer->SpeedUpdate();
	
	// if (FMath::IsNearlyEqual(Rotation.Roll, -10.f, 9.f) && bDoARoll == true)
	// {
	// 	bDoARoll = false;
	// 	// Sphere->AddImpulse(GetActorForwardVector() * Sphere->GetMass()* 3000.f);
	// 	PlayerMesh->SetRelativeRotation(FRotator(Rotation.Pitch, Rotation.Yaw, 0.f));
	// }
	
	if (MoveForce > 0.f)
	{
		CameraPos = Speed * 800.f;
		PawnMovementComponent->MaxSpeed = MaxMoveSpeed;
		PawnMovementComponent->Acceleration = MaxMoveSpeed/15.f;
	}
	else if (MoveForce < 0.f)
	{
		CameraPos = 300.f;
		PawnMovementComponent->MaxSpeed = MaxMoveSpeed/2;
		PawnMovementComponent->Acceleration = MaxMoveSpeed/5.f;
	}
	AddMovementInput(Sphere->GetForwardVector(), MoveForce);

	// scuffed custom friction/deceleration
	if (Speed > 0.01f && MoveForce == 0.f)
	{
		Velocity.Normalize();
		AddMovementInput(-1*Velocity, Speed-0.01f);
	}
	
	Sphere->AddTorqueInRadians(GetActorUpVector() * TurnSpeed * 450000);
	
	if (bDoARoll == true)
	{
		PlayerMesh->SetRelativeRotation(FMath::RInterpTo(Rotation, FRotator(Rotation.Pitch, Rotation.Yaw, Rotation.Roll + 13.f), DeltaTime, 40.f));
	}
	else
	{
		
	}
	
	// if (MoveForce > 0.f)
	// {
	// 	if (PlayerMesh->GetRelativeRotation().Pitch > -7.f)
	// 	{
	// 		// PlayerMesh->AddTorqueInRadians(GetActorRightVector() * PitchRadian * 3000);
	// 		PlayerMesh->AddRelativeRotation(FRotator(-0.1f, 0.f, 0.f));
	// 	}
	// }
	// else if (MoveForce < 0.f)
	// {
	// 	if (PlayerMesh->GetRelativeRotation().Pitch < 10.f)
	// 	{
	// 		// PlayerMesh->AddTorqueInRadians(GetActorRightVector() * PitchRadian * 6000);
	// 		PlayerMesh->AddRelativeRotation(FRotator(0.1f, 0.f, 0.f));
	// 	}
	// }
}

// Called to bind functionality to input
void APlayerCar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &APlayerCar::Drive);
	PlayerInputComponent->BindAxis("TurnL", this, &APlayerCar::Turn);

	PlayerInputComponent->BindAction("ShootLaser", IE_Pressed, this, &APlayerCar::ShootLaser);
	PlayerInputComponent->BindAction("ShootMissile", IE_Pressed, this, &APlayerCar::ShootMissile);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &APlayerCar::Reload);
	PlayerInputComponent->BindAction("AileronRoll", IE_Pressed, this, &APlayerCar::AileronRoll);
	PlayerInputComponent->BindAction("BackCam", IE_Pressed, this, &APlayerCar::BackCamOn);
	PlayerInputComponent->BindAction("BackCam", IE_Released, this, &APlayerCar::BackCamOff);
	PlayerInputComponent->BindAction("ToggleTopDown", IE_Pressed, this, &APlayerCar::ToggleTopCam);
}

void APlayerCar::Drive(float Force)
{
	MoveForce = Force;
	PitchRadian = Force;
}

void APlayerCar::Turn(float TurnDirection)
{
	TurnSpeed = TurnDirection;
	// if (FMath::IsNearlyEqual(MoveForce, 0.f, 0.1f) && !FMath::IsNearlyEqual(TurnSpeed, 0.f, 0.1f))
	// 	AddMovementInput(Sphere->GetForwardVector(), 1);
}

void APlayerCar::ShootLaser()
{
	if (Ammo <= 0)
	{
		// GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, FString::Printf(TEXT("No ammo. Reload")));
		AmmoCounter->SetColorAndOpacity(FLinearColor(255, 0, 0));

	}
	if (Ammo > 0)
	{
		UWorld* World = GetWorld();
		const FVector Location = GetActorLocation();
		// const FVector Right = PlayerMesh->GetRightVector();
		
		if (bShotgun == true)
		{
			TArray<ABullet*> Bullets;
			Ammo -= 3;
			if (Ammo < 0)
			{
				Ammo = 0;
			}
			UGameplayStatics::PlaySound2D(World, ShootingSound, 1.0f, 1.0f, 0.0f);
			//implement TArray of actors and so on
			Bullets.Emplace(World->SpawnActor<ABullet>(LaserToSpawn, Location + GetActorForwardVector() * 100.f + GetActorRightVector() * -50.f, GetActorRotation()));
			Bullets.Emplace(World->SpawnActor<ABullet>(LaserToSpawn,Location + GetActorForwardVector() * 100.f, GetActorRotation()));
			Bullets.Emplace(World->SpawnActor<ABullet>(LaserToSpawn, Location + GetActorForwardVector() * 100.f + GetActorRightVector() * 50.f, GetActorRotation()));
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
				Bullet = World->SpawnActor<ABullet>(LaserToSpawn, Location + GetActorForwardVector() * 100.f, GetActorRotation());
				UGameplayStatics::PlaySound2D(World, ShootingSound, 1.0f, 1.0f, 0.0f);
				if (Bullet)
				{
					Bullet->OnBulletHitEnemy.AddDynamic(this, &APlayerCar::OnEnemyHit);
				}
			}
		}
	}
	AmmoCounter->AmmoUpdate();
	UE_LOG(LogTemp, Warning, TEXT("Shooting Laser"));

}

void APlayerCar::ShootMissile()
{
	if (Ammo <= 0)
	{
		// GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, FString::Printf(TEXT("No ammo. Reload")));
		AmmoCounter->SetColorAndOpacity(FLinearColor(255, 0, 0));

	}
	if (Ammo > 0)
	{
		UWorld* World = GetWorld();
		const FVector Location = GetActorLocation();
		// const FVector Right = PlayerMesh->GetRightVector();
		
		if (bShotgun == true)
		{
			TArray<ABullet*> Bullets;
			Ammo -= 3;
			if (Ammo < 0)
			{
				Ammo = 0;
			}
			UGameplayStatics::PlaySound2D(World, ShootingSound, 1.0f, 1.0f, 0.0f);
			//implement TArray of actors and so on
			Bullets.Emplace(World->SpawnActor<ABullet>(MissileToSpawn, Location + GetActorForwardVector() * 100.f + GetActorRightVector() * -50.f, GetActorRotation()));
			Bullets.Emplace(World->SpawnActor<ABullet>(MissileToSpawn,Location + GetActorForwardVector() * 100.f, GetActorRotation()));
			Bullets.Emplace(World->SpawnActor<ABullet>(MissileToSpawn, Location + GetActorForwardVector() * 100.f + GetActorRightVector() * 50.f, GetActorRotation()));
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
				Bullet = World->SpawnActor<ABullet>(MissileToSpawn, Location + GetActorForwardVector() * 100.f, GetActorRotation());
				UGameplayStatics::PlaySound2D(World, ShootingSound, 1.0f, 1.0f, 0.0f);
				if (Bullet)
				{
					Bullet->OnBulletHitEnemy.AddDynamic(this, &APlayerCar::OnEnemyHit);
				}
			}
		}
	}
	AmmoCounter->AmmoUpdate();
	UE_LOG(LogTemp, Warning, TEXT("Shooting Missile"));
}

void APlayerCar::OnEnemyHit(AActor* Actor)
{
	if (Actor->IsA<AEnemy>())
	{
		Cast<AEnemy>(Actor)->IsHit();
		if (RacingGameMode)
		{
			RacingGameMode->EnemyDied();
			if (Bullet)
			{
				Bullet->Death();
			}
		}
	}
	else if (Actor->IsA<AEnemyC>())
	{
		Cast<AEnemyC>(Actor)->IsHit();
		if (RacingGameMode)
		{
			RacingGameMode->EnemyDied();
			if (Bullet)
			{
				Bullet->Death();
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Enemy killed"));
}

void APlayerCar::ShotgunPU()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("SHOTGUN")));
	bShotgun = true;
}

void APlayerCar::SpeedPU()
{
	const auto World = GetWorld();
	// CommandString = "r.MotionBlur.Amount 0.5";
	// World->Exec(World, *CommandString);
	// Camera->PostProcessSettings.WeightedBlendables.Array[0].Weight = 0.2;
	PawnMovementComponent->MaxSpeed = MaxMoveSpeed*3;
	// SpringArm->CameraLagSpeed = 10.f;
	Sphere->AddImpulse(PlayerMesh->GetForwardVector() * Sphere->GetMass()* 2000.f);
	HoverForce = DefaultHoverForce * 1.5f;
	RoadTest = World->GetCurrentLevel()->GetName();
	GravityForce = DefaultGravityForce * 0.15f;
	TraceLength = DefaultTraceLength + 50.f;
	SpeedLimit();
}

void APlayerCar::SpeedLimit()
{
	TimerDelegateSpeed.BindLambda([&]
	{
		const auto World = GetWorld();
		// SpringArm->CameraLagSpeed = 20.f;
		if (World->GetCurrentLevel()->GetName() == RoadTest)
		{
			PawnMovementComponent->MaxSpeed = MaxMoveSpeed;
			HoverForce = DefaultHoverForce;
			TraceLength = DefaultTraceLength;
			GravityForce = DefaultGravityForce;
			BackCamOff();
			// Camera->PostProcessSettings.WeightedBlendables.Array[0].Weight = 0;
		}
		// CommandString = "r.MotionBlur.Amount 0";
		// World->Exec(World, *CommandString);
	});

	GetWorld()->GetTimerManager().SetTimer(TimerHandleSpeed, TimerDelegateSpeed, 3.f, false);
}

void APlayerCar::Reload()
{
	if (bIsReloading == false)
	{
		bIsReloading = true;
		const auto World = GetWorld();
		UGameplayStatics::PlaySound2D(World, ReloadingSound, 1.f, 1.f, 0.f, 0);
		// GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Yellow, FString::Printf(TEXT("Reloading... (takes 1 second)")));
	
		TimerDelegateReload.BindLambda([&]
			{
				Ammo = 20;
				AmmoCounter->SetColorAndOpacity(FLinearColor(255, 255, 255));
				// GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Reloaded")));
				AmmoCounter->AmmoUpdate();
			bIsReloading = false;
			});

		GetWorld()->GetTimerManager().SetTimer(TimerHandleReload, TimerDelegateReload, 1.f, false);
	}
}

void APlayerCar::AileronRoll()
{
	const auto World = GetWorld();
	Timer = World->GetTimeSeconds();
	if (Timer > TimeSinceEvent)
	{
		bDoARoll = true;
		TimeSinceEvent = Timer + 3.f;
		TimerDelegateRoll.BindLambda([&]
		{
			// PlayerMesh->SetRelativeRotation(FRotator(Rotation.Pitch, Rotation.Yaw, 0.f));
			bDoARoll = false;
		});
		GetWorld()->GetTimerManager().SetTimer(TimerHandleRoll, TimerDelegateRoll, 0.7f, false);
	}
}

int APlayerCar::GetAmmo()
{
	return Ammo;
}

int APlayerCar::GetMaxAmmo()
{
	return MaxAmmo;
}

int APlayerCar::GetHealth()
{
	return Health;
}

int APlayerCar::GetMaxHealth()
{
	return MaxHealth;
}

void APlayerCar::HealthPack()
{
	if (Health < 3)
		Health++;
	HealthBar->HealthUpdate();
}

float APlayerCar::GetSpeed()
{
	if (MoveForce < 0.f)
	{
		return 0.f;
	}
	return Speed;
}

void APlayerCar::BackCamOn()
{
	Camera->Deactivate();
	Back_Camera->Activate();
}

void APlayerCar::BackCamOff()
{
	Back_Camera->Deactivate();
	Top_Camera->Deactivate();
	// if (!FollowHealthBar->IsVisible())
	FollowHealthBar->SetVisibility(ESlateVisibility::Visible);
	HealthBar->RemoveFromViewport();
	Camera->Activate();
}

void APlayerCar::ToggleTopCam()
{
	if (bTopCam == false)
	{
		Camera->Deactivate();
		Back_Camera->Deactivate();
		Top_Camera->Activate();
		HealthBar->AddToViewport();
		FollowHealthBar->SetVisibility(ESlateVisibility::Hidden);
		bTopCam = true;
	}
	
	else if (bTopCam == true)
	{
		Camera->Activate();
		Back_Camera->Activate();
		Top_Camera->Deactivate();
		HealthBar->RemoveFromViewport();
		FollowHealthBar->SetVisibility(ESlateVisibility::Visible);
		bTopCam = false;
	}
}

float APlayerCar::GetTAtkTime()
{
	return TAtkTime;
}

void APlayerCar::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                           UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const auto World = GetWorld();
	Timer = World->GetTimeSeconds();
	if (OtherActor->IsA<AEnemy>() || OtherActor->IsA<AEnemyC>())
	{
		if (Timer > TimeSinceEvent)
		{
			Health--;
			FollowHealthBar->HealthUpdate();
			HealthBar->HealthUpdate();
			if (Health <= 0)
			{
				RacingGameMode->GameOver( "Damage from enemies" );
			}
			TimeSinceEvent = Timer + 1.5f;
		}
	}
}

