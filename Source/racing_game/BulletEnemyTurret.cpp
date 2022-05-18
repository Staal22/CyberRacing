// Fill out your copyright notice in the Description page of Project Settings.

#include "BulletEnemyTurret.h"
#include <Components/SphereComponent.h>
#include "PlayerCar.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABulletEnemyTurret::ABulletEnemyTurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Setting up box collision and making it root component
	Root = CreateDefaultSubobject<USphereComponent>(TEXT("Root/Collision"));
	SetRootComponent(Root);
	
	//Setting up mesh and attach it to root
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));//Mesh set in BP
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
	//update bullet location
	Root->AddRelativeLocation(BulletMesh->GetForwardVector() * Speed * DeltaTime);
	
	//Update time lived
	TimeLived += DeltaTime;
	if (TimeLived >= TimeToLive)//>10secs
	{
		//trigger death
		this->Death();
	}
}

void ABulletEnemyTurret::Death()
{
	//explosions fx	
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionUponDeath, GetTransform(), true);
	//death sound
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation(), 0.2f);
	//removes actor from world instance
	Destroy();																								
}

void ABulletEnemyTurret::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//dont do anything if collides with self
	if (OtherActor->IsA<ABulletEnemyTurret>())															
	{
		return;
	}
	//calls function in player class
	if (OtherActor->IsA<APlayerCar>())
	{
		OnBulletHitEnemy.Broadcast(OtherActor);																
	}
}

