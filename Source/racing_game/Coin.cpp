// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "PlayerCar.h"

// Sets default values
ACoin::ACoin()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(Collision);

	CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoinMesh"));
	CoinMesh->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnOverlapBegin);
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Turn += DeltaTime;
	if (Turn > 9.f)
	{
		Turn = 0.f;
	}

	CoinMesh->SetRelativeRotation(FRotator(30.f, Turn * 40, 0.f));
}

void ACoin::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor == this)
		return;


	UE_LOG(LogTemp, Warning, TEXT("%s overlapping with %s at location %s"), *GetName(),
		*OtherActor->GetName(),
		*GetActorLocation().ToString());


	OnCoinHitPlayer.Broadcast(OtherActor);

	if (OtherActor->IsA<APlayerCar>())
	{
		//Cast<APlayerCar>(OtherActor)->CoinPU();
		Destroy();
		UE_LOG(LogTemp, Warning, TEXT("Coin obtained"));
	}

}

