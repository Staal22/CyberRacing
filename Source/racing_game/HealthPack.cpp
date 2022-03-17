// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPack.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "PlayerCar.h"
#include "PowerUpSpawner.h"

// Sets default values
AHealthPack::AHealthPack()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(Collision);

	HPMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HPMesh"));
	HPMesh->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AHealthPack::BeginPlay()
{
	Super::BeginPlay();
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AHealthPack::OnOverlapBegin);
	
	RacingGameMode = Cast<Aracing_gameGameModeBase>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void AHealthPack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	bounceTime += DeltaTime;
	if (bounceTime < 1.f && bounceUp == true)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorUpVector() * Speed * DeltaTime;
		SetActorLocation(NewLocation);
	}
	if (bounceTime > 1.f && bounceUp == true)
	{
		bounceUp = false;
		bounceTime = 0.f;
	}
	if (bounceTime < 1.f && bounceUp == false)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorUpVector() * Speed * -1 * DeltaTime;
		SetActorLocation(NewLocation);
		//UE_LOG(LogTemp, Warning, TEXT(" cock and balls, even"));
	}
	if (bounceTime > 1.f && bounceUp == false)
	{
		bounceUp = true;
		bounceTime = 0.f;
	}

	Turn += DeltaTime;
	if (Turn > 9.f)
	{
		Turn = 0.f;
	}

	HPMesh->SetRelativeRotation(FRotator(30.f, Turn * 40, 0.f));

}

void AHealthPack::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor == this)
		return;


	UE_LOG(LogTemp, Warning, TEXT("%s overlapping with %s at location %s"), *GetName(),
		*OtherActor->GetName(),
		*GetActorLocation().ToString());


	OnHealthPackHitPlayer.Broadcast(OtherActor);

	if (OtherActor->IsA<APlayerCar>())
	{
		if (Cast<APlayerCar>(OtherActor)->GetHealth() < 3)
			Cast<APlayerCar>(OtherActor)->HealthPack();
		else
		{
			RacingGameMode->CoinAcquired();
		}
		Destruction();
		UE_LOG(LogTemp, Warning, TEXT("HealthPack power-up obtained"));
	}

}

void AHealthPack::Destruction()
{
	OnHPDestroyed.Broadcast();
	Destroy();
}

