// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "PlayerCar.h"
#include "racing_gameGameModeBase.h"
#include "AICar.h"

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
	// when collision is detected run OnOverlapBegin
	Super::BeginPlay();
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnOverlapBegin);
	
	const auto World = GetWorld();
	RacingGameMode = Cast<Aracing_gameGameModeBase>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//rotating the coin a full rotation for 9 seconds then after a full turn the float is reset to 0 (9*40 = 360)
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
	// if statement to make sure the coin doesnt "collide with itself"
	if (OtherActor == this)
		return;


	UE_LOG(LogTemp, Warning, TEXT("%s overlapping with %s at location %s"), *GetName(),
		*OtherActor->GetName(),
		*GetActorLocation().ToString());


	OnCoinHitPlayer.Broadcast(OtherActor);

	//if the object that overlaps the coin is PlayerCar run the CoinAcquired function in RacingGameMode and destroy the checkpoint
	if (OtherActor->IsA<APlayerCar>())
	{
		//Cast<APlayerCar>(OtherActor)->CoinPU();
		if (RacingGameMode)
		{
			RacingGameMode->CoinAcquired();
		}
		Destroy();
		UGameplayStatics::PlaySound2D(GetWorld(), PickUpSound, 1.f, 1.f, 0.f, 0);
		UE_LOG(LogTemp, Warning, TEXT("Coin obtained"));
	}
	else if (OtherActor->IsA<AAICar>())
	{
		Destroy();
	}

}

