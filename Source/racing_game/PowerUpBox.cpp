// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpBox.h"
#include "AICar.h"
#include "PlayerCar.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APowerUpBox::APowerUpBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(Collision);

	PUBMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PUBMesh"));
	PUBMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void APowerUpBox::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &APowerUpBox::OnOverlapBegin);
}

// Called every frame
void APowerUpBox::Tick(float DeltaTime)
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

	PUBMesh->SetRelativeRotation(FRotator(45.f, Turn * 40, 45.f));

}

void APowerUpBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor == this)
		return;

	if (OtherActor->IsA<APlayerCar>())
	{
		randint = FMath::RandRange(1, 2);
		if (randint == 1)
		{
			Cast<APlayerCar>(OtherActor)->ShotgunPU();
		}
		else if (randint == 2)
		{
			Cast<APlayerCar>(OtherActor)->MinePU();
		}
		Destruction();
	}
	else if (OtherActor->IsA<AAICar>())
	{
		randint = FMath::RandRange(1, 2);
		if (randint == 1)
		{
			Cast<AAICar>(OtherActor)->MineFlip();
			Cast<AAICar>(OtherActor)->PUActive();
		}
		Destruction();
	}
}

void APowerUpBox::Destruction()
{
	OnPUDestroyed.Broadcast();
	Destroy();
}
