// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCar.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include <Components/WidgetComponent.h>
#include "AmmoCounter.h"
#include "DrawDebugHelpers.h"
#include <Kismet/GameplayStatics.h>
#include "Bullet.h"
#include "Enemy.h"
#include "racing_gameGameModeBase.h"
#include "ScoreCounter.h"
#include "Components/BoxComponent.h"


// Sets default values
APlayerCar::APlayerCar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	//SetRootComponent(Box);

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	//PlayerMesh->SetupAttachment(GetRootComponent());
	SetRootComponent(PlayerMesh);

	PawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMoveComp"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetUsingAbsoluteRotation(false);
	SpringArm->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 800;
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 20.f;
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetRelativeLocation(FVector(3000.f, 0.f, 100.f));


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	AmmoComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	AmmoComp->SetupAttachment(PlayerMesh);
	Ammo = MaxAmmo;

	ScoreComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("ScoreCounter"));
	ScoreComp->SetupAttachment(PlayerMesh);


}

// Called when the game starts or when spawned
void APlayerCar::BeginPlay()
{
	Super::BeginPlay();
	
	//Forward = GetActorForwardVector();
	UWorld* World = GetWorld();
	RacingGameMode = Cast<Aracing_gameGameModeBase>(GetWorld()->GetAuthGameMode());

	AmmoCounter = Cast<UAmmoCounter>(AmmoComp->GetUserWidgetObject());
	AmmoCounter->SetOwner(this);
	AmmoCounter->AmmoUpdate();

	ScoreCounter = Cast<UScoreCounter>(ScoreComp->GetUserWidgetObject());
	ScoreCounter->SetOwner(this);
	ScoreCounter->ScoreUpdate();

}

// Called every frame
void APlayerCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UWorld* World = GetWorld();
	//if (FVector::DotProduct(GetVelocity().GetSafeNormal(), GetActorForwardVector()) < 0.f)
	//{
	//	PawnMovementComponent->MaxSpeed = 400;
	//	PawnMovementComponent->Acceleration = 100;
	//}
	//else
	//{
	//	PawnMovementComponent->MaxSpeed = 800;
	//	PawnMovementComponent->Acceleration = 400;
	//}
	DrawDebugLine(World, GetActorLocation() + GetActorForwardVector() * -20.f + GetActorRightVector() * -50.f, GetActorLocation() + GetActorForwardVector() * -60.f + GetActorRightVector() * -50.f, FColor(0, 0, 255), false, 3.0f, 0.0f, 4.0f);
	DrawDebugLine(World, GetActorLocation() + GetActorForwardVector() * -20.f + GetActorRightVector() * 50.f, GetActorLocation() + GetActorForwardVector() * -60.f + GetActorRightVector() * 50.f, FColor(0, 0, 255), false, 3.0f, 0.0f, 4.0f);

	FRotator NoRoll = GetActorRotation();
	NoRoll.Roll = 0.f;
	PlayerMesh->SetRelativeRotation(NoRoll);

	//PlayerMesh->AddRelativeLocation(FVector(0.f, TurnSpeed, 0.f));
	
	AddMovementInput(GetActorForwardVector(), MoveSpeed);

	PlayerMesh->AddTorqueInRadians(GetActorUpVector() * TurnSpeed * 250000);

	if (MoveSpeed > 0.f)
	{
		if (GetActorRotation().Pitch > -5.f)
		{
			PlayerMesh->AddTorqueInRadians(GetActorRightVector() * PitchRadian * 3000);
		}
	}
	else if (MoveSpeed < 0.f)
	{
		if (GetActorRotation().Pitch < 5.f)
		{
			PlayerMesh->AddTorqueInRadians(GetActorRightVector() * PitchRadian * 6000);
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
	PlayerInputComponent->BindAction("Boost", IE_Pressed, this, &APlayerCar::BoostOn);
	PlayerInputComponent->BindAction("Boost", IE_Released, this, &APlayerCar::BoostOff);
}

void APlayerCar::Drive(float Force)
{
	MoveSpeed = Force;
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
			GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, FString::Printf(TEXT(" %d "), Ammo), false);
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
	UWorld* World = GetWorld();
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

float APlayerCar::GetAmmo()
{
	return Ammo;
}

void APlayerCar::BoostOn()
{
	if (PawnMovementComponent->Acceleration != 270)
	{
		PawnMovementComponent->Acceleration = 270;
	}
}

void APlayerCar::BoostOff()
{
	if (PawnMovementComponent->Acceleration != 210)
	{
		PawnMovementComponent->Acceleration = 210;
	}
}

float APlayerCar::GetMaxAmmo()
{
	return MaxAmmo;
}

