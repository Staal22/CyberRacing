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
	SpringArm->SetRelativeRotation(FRotator(-35.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 600;
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 5.f;
	SpringArm->SetupAttachment(PlayerMesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	AmmoComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	AmmoComp->SetupAttachment(GetRootComponent());

	Ammo = MaxAmmo;



}

// Called when the game starts or when spawned
void APlayerCar::BeginPlay()
{
	Super::BeginPlay();
	
	AmmoCounter = Cast<UAmmoCounter>(AmmoComp->GetUserWidgetObject());
	AmmoCounter->SetOwnerShip(this);

	AmmoCounter->AmmoUpdate();
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
			//RacingGameMode->EnemyDied();
		}
		//ScoreCounter->ScoreUpdate();
		Bullet->Destroy();
	}

	UE_LOG(LogTemp, Warning, TEXT("Enemy killed"));
}

void APlayerCar::Shoot()
{
	Ammo--;
	AmmoCounter->AmmoUpdate();

	if (Ammo > 0)
	{
		Ammo--;
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, FString::Printf(TEXT(" %d "), Ammo), false);

		UWorld* World = GetWorld();

		if (World)
		{
			FVector Location = GetActorLocation();
			Bullet = World->SpawnActor<ABullet>(BulletToSpawn, Location + FVector(150.f, 0.f, 0.f), GetActorRotation());
			//UGameplayStatics::PlaySound2D(World, ShootingSound, 1.0f, 1.0f, 0.0f, 0);

			if (Bullet)
			{
				Bullet->OnBulletHitEnemy.AddDynamic(this, &APlayerCar::OnEnemyHit);
			}
		}

		if (Ammo == 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, FString::Printf(TEXT("No ammo. Reload")));

		}

	}

	UE_LOG(LogTemp, Warning, TEXT("Shooting"));

}

float APlayerCar::GetAmmo()
{
	return Ammo;
}

float APlayerCar::GetMaxAmmo()
{
	return MaxAmmo;
}

