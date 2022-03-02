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


// Sets default values
APlayerCar::APlayerCar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	//SetRootComponent(Arrow);

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	SetRootComponent(PlayerMesh);

	PawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMoveComp"));
	

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->SetRelativeRotation(FRotator(-25.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 800;
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 5.f;
	SpringArm->SetupAttachment(PlayerMesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	AmmoComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	AmmoComp->SetupAttachment(GetRootComponent());
	Ammo = MaxAmmo;

	ScoreComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("ScoreCounter"));
	ScoreComp->SetupAttachment(GetRootComponent());


}

// Called when the game starts or when spawned
void APlayerCar::BeginPlay()
{
	Super::BeginPlay();
	
	FVector InitLocation = GetActorLocation();
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
	DrawDebugLine(World, GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 15.f, FColor(255, 0, 0), false, 3.0f, 0.0f, 4.0f);

}

// Called to bind functionality to input
void APlayerCar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &APlayerCar::Drive);
	PlayerInputComponent->BindAxis("TurnL", this, &APlayerCar::Turn);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerCar::Shoot);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &APlayerCar::Reload);
}

void APlayerCar::Drive(float Force)
{
	AddMovementInput(GetActorForwardVector(), Force);
}

void APlayerCar::Turn(float TurnDirection)
{
	PlayerMesh->AddRelativeRotation(FRotator(0.f, TurnDirection, 0.f));
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
			Bullets.Emplace(World->SpawnActor<ABullet>(BulletToSpawn, Location + GetActorForwardVector() * 100.f + FVector::CrossProduct(GetActorForwardVector(), GetActorUpVector() * -50.f), GetActorRotation()));
			Bullets.Emplace(World->SpawnActor<ABullet>(BulletToSpawn, Location + GetActorForwardVector() * 100.f, GetActorRotation()));
			Bullets.Emplace(World->SpawnActor<ABullet>(BulletToSpawn, Location + GetActorForwardVector() * 100.f + FVector::CrossProduct(GetActorForwardVector(), GetActorUpVector() * 50.f), GetActorRotation()));
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
				Bullet = World->SpawnActor<ABullet>(BulletToSpawn, Location + FVector(150.f, 0.f, 0.f), GetActorRotation());
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

float APlayerCar::GetMaxAmmo()
{
	return MaxAmmo;
}

