// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "PlayerCar.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(Collision);

	CPMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CPMesh"));
	CPMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlapBegin);

}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckpoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor == this)
		return;


	UE_LOG(LogTemp, Warning, TEXT("%s overlapping with %s at location %s"), *GetName(),
		*OtherActor->GetName(),
		*GetActorLocation().ToString());


	OnCheckpointHitPlayer.Broadcast(OtherActor);

	if (OtherActor->IsA<APlayerCar>())
	{
		Cast<APlayerCar>(OtherActor)->Checkpoint();
		UE_LOG(LogTemp, Warning, TEXT("Check pointed"));

		Destroy();
	}

}