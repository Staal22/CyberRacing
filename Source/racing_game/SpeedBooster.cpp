// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedBooster.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "PlayerCar.h"

// Sets default values
ASpeedBooster::ASpeedBooster()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(Collision);

	SBMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SBMesh"));
	SBMesh->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ASpeedBooster::BeginPlay()
{
	Super::BeginPlay();
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ASpeedBooster::OnOverlapBegin);

}

// Called every frame
void ASpeedBooster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpeedBooster::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor == this)
		return;


	UE_LOG(LogTemp, Warning, TEXT("%s overlapping with %s at location %s"), *GetName(),
		*OtherActor->GetName(),
		*GetActorLocation().ToString());


	OnSpeedBoosterHitPlayer.Broadcast(OtherActor);

	if (OtherActor->IsA<APlayerCar>())
	{
		Cast<APlayerCar>(OtherActor)->SpeedPU();
		UE_LOG(LogTemp, Warning, TEXT("Speed boosted"));
	}

}

