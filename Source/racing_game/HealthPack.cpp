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
	// when collision is detected run OnOverlapBegin
	Super::BeginPlay();
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AHealthPack::OnOverlapBegin);
	
	RacingGameMode = Cast<Aracing_gameGameModeBase>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void AHealthPack::Tick(float DeltaTime)
{
	// turning and "bouncing" the object
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
		//UE_LOG(LogTemp, Warning, TEXT(" "));
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
	// if statement to make sure the object doesnt "collide with itself"
	if (OtherActor == this)
		return;


	UE_LOG(LogTemp, Warning, TEXT("%s overlapping with %s at location %s"), *GetName(),
		*OtherActor->GetName(),
		*GetActorLocation().ToString());


	OnHealthPackHitPlayer.Broadcast(OtherActor);
	//if the object that overlaps the healthpack is PlayerCar run the GetHealth and HealthPack functions in PlayerCar
	//if health is full run CoinAcquired which grants the player 1000 points
	//then run Destruction()
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
//broadcast to PowerUpSpawner, then destroy the healthpack object
void AHealthPack::Destruction()
{
	OnHPDestroyed.Broadcast();
	Destroy();
}

