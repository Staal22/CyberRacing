// Fill out your copyright notice in the Description page of Project Settings.


#include "Shotgun.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "PlayerCar.h"
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
	// when collision is detected run OnOverlapBegin
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AShotgun::OnOverlapBegin);
	
}

// Called every frame
void AShotgun::Tick(float DeltaTime)
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

	ShotgunMesh->SetRelativeRotation(FRotator(30.f, Turn*40, 0.f));
}

void AShotgun::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	// if statement to make sure the object doesnt "collide with itself"
	if (OtherActor == this)
		return;


	UE_LOG(LogTemp, Warning, TEXT("%s overlapping with %s at location %s"), *GetName(),
		*OtherActor->GetName(),
		*GetActorLocation().ToString());


	OnPowerUpHitPlayer.Broadcast(OtherActor);
	//if the object that overlaps the shotgun is PlayerCar run the ShotgunPU function in PlayerCar
	//then run Destruction()
	if (OtherActor->IsA<APlayerCar>())
	{
		Cast<APlayerCar>(OtherActor)->ShotgunPU();
		Destruction();
		UE_LOG(LogTemp, Warning, TEXT("Shotgun power-up obtained"));
	}

}
//broadcast to PowerUpSpawner, then destroy the shotgun object
void AShotgun::Destruction()
{
	OnPUDestroyed.Broadcast();
	Destroy();
}
