// Fill out your copyright notice in the Description page of Project Settings.


#include "Mine.h"
#include "AICar.h"
#include "Enemy.h"
#include "EnemyC.h"
#include "PlayerCar.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMine::AMine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(Collision);

	MineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MineMesh"));
	MineMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AMine::BeginPlay()
{
	Super::BeginPlay();
	//Collision->OnComponentBeginOverlap.AddDynamic(this, &AMine::OnOverlapBegin);


}

// Called every frame
void AMine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	BombTime += DeltaTime;
	ActTime += DeltaTime;

	if (BombTime > 1.5)
	{
		Explosion();
	}

}

void AMine::Explosion()
{

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MineExplosion, GetTransform(), true);

	GetOverlappingActors(Result, AAICar::StaticClass());
	GetOverlappingActors(Result, APlayerCar::StaticClass());

	for (int i = 0; i < Result.Num(); i++)
	{
		if (Result[i]->IsA<AAICar>())
		{
			Cast<AAICar>(Result[i])->Missile();
		}
		else if (Result[i]->IsA<APlayerCar>())
		{
			Cast<APlayerCar>(Result[i])->HitByMissile();
		}
		else if (Result[i]->IsA<AEnemy>())
		{
			Cast<AEnemy>(Result[i])->IsHit();
		}
		else if (Result[i]->IsA<AEnemyC>())
		{
			Cast<AEnemyC>(Result[i])->IsHit();
		}
	}

	//for (int i = 0; i < 2; i++)
	//{
	//	if (Result[i]->IsA<APlayerCar>())
	//	{
	//		/*OnOverlapBegin();*/
	//	}
	//}

	Destroy();
}

//void AMine::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
//	UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex, bool bFromSweep,
//	const FHitResult& SweepResult)
//{
//	// if statement to make sure the coin doesnt "collide with itself"
//	if (OtherActor == this)
//		return;
//
//	OnMineHitCar.Broadcast(OtherActor);
//
//	//if the object that overlaps the coin is PlayerCar run the CoinAcquired function in RacingGameMode and destroy the checkpoint
//	if (HitCar == true) 
//	{
//		if (OtherActor->IsA<APlayerCar>())
//		{
//			return;
//		}
//		else if (OtherActor->IsA<AAICar>())
//		{
//			Cast<AAICar>(OtherActor)->Missile();
//		}
//	}
//
//}
