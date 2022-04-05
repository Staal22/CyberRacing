// Fill out your copyright notice in the Description page of Project Settings.

#include "BulletEnemyTurret.h"
#include <Components/SphereComponent.h>
// #include "Enemy.h"
#include "PlayerCar.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABulletEnemyTurret::ABulletEnemyTurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USphereComponent>(TEXT("Root/Collision"));
	SetRootComponent(Root);

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	BulletMesh->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ABulletEnemyTurret::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletEnemyTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Root->AddRelativeLocation(BulletMesh->GetForwardVector() * Speed * DeltaTime);
	
	TimeLived += DeltaTime;

	if (TimeLived >= TimeToLive)
	{
		this->Death();
	}
}

void ABulletEnemyTurret::Death()
{
	//explosions fx
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionUponDeath, GetTransform(), true);
	//death sound
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
	Destroy();
	
}

void ABulletEnemyTurret::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<ABulletEnemyTurret>())
	{
		return;
	}

	if (OtherActor->IsA<APlayerCar>())
	{
		OnBulletHitEnemy.Broadcast(OtherActor);
	}
}

