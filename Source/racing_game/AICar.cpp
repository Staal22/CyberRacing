// Fill out your copyright notice in the Description page of Project Settings.


#include "AICar.h"

// Sets default values
AAICar::AAICar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(Collision);

	AICarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AICarMesh"));
	AICarMesh->SetupAttachment(GetRootComponent());
	LineTrace();
}

// Called when the game starts or when spawned
void AAICar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAICar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAICar::LineTrace()
{
	//Re-initialize hit info
	FHitResult* Hit = new FHitResult();
	FVector Start = GetActorLocation();
	FVector End = Start + FVector(0, -2500, 0);
	//call GetWorld() from within an actor extending class
	GetWorld()->LineTraceSingleByChannel(*Hit, Start, End, ECC_Visibility); //ECC_Pawn
	if (Hit)
	{
		UKismetSystemLibrary::DrawDebugLine(GetWorld(), Start, End, FColor(100, 0, 0));
		UKismetSystemLibrary::DrawDebugSphere(GetWorld(), Hit->Location, 5, 5, FLinearColor::Red);
	}
	else
	{
		UKismetSystemLibrary::DrawDebugLine(GetWorld(), Start, End, FColor(100, 0, 0));
		UKismetSystemLibrary::DrawDebugSphere(GetWorld(), End, 5, 5, FLinearColor::White);
	}
}