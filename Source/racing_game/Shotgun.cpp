// Fill out your copyright notice in the Description page of Project Settings.


#include "Shotgun.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
//#include "Player.h"
#include "PowerUpSpawner.h"

// Sets default values
AShotgun::AShotgun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(Collision);

	ShotgunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShotgunMesh"));
	ShotgunMesh->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AShotgun::BeginPlay()
{
	Super::BeginPlay();
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AShotgun::OnOverlapBegin);
	
}

// Called every frame
void AShotgun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShotgun::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor == this)
		return;


	UE_LOG(LogTemp, Warning, TEXT("%s overlapping with %s at location %s"), *GetName(),
		*OtherActor->GetName(),
		*GetActorLocation().ToString());


	OnPowerUpHitPlayer.Broadcast(OtherActor);

	// edit cast here
	//if (OtherActor->IsA<APlayerCar>())
	//{
	//	a cast to activate shotgun powerup here
	//  Destruction();
	//	UE_LOG(LogTemp, Warning, TEXT("PowerUp obtained"));
	//}

}

void AShotgun::Destruction()
{
	OnPUDestroyed.Broadcast();
	Destroy();
}
