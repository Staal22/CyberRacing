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

}

// Called when the game starts or when spawned
void AAICar::BeginPlay()
{
	Super::BeginPlay();
	
	//RacingGameMode = Cast<Aracing_gameGameModeBase>(GetWorld()->GetAuthGameMode());

	//CarDirection = ASplineClass::GetSpline()->GetActorLocation()-GetActorLocation();
	//CarDirection.Normalize();
	//SetActorRotation(CarDirection.Rotation());
}

// Called every frame
void AAICar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LineTrace();
	Time += DeltaTime;

	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorForwardVector() * Speed * Time;
	SetActorLocation(NewLocation);
}

void AAICar::LineTrace()
{
	//Re-initialize hit info
	//call GetWorld() from within an actor extending class
	FHitResult* Hit = new FHitResult();
	FVector Start = GetActorLocation();
	FVector End = Start + FVector(0, 0, -HoverHeight);
	GetWorld()->LineTraceSingleByChannel(*Hit, Start, End, ECC_Visibility); //ECC_Pawn
	if (Hit)
	{
		UE_LOG(LogTemp, Warning, TEXT("123linetrace"))
		UKismetSystemLibrary::DrawDebugLine(GetWorld(), Start, End, FColor(100, 0, 0));
		UKismetSystemLibrary::DrawDebugSphere(GetWorld(), Hit->Location, 5, 5, FLinearColor::Red);
		Ruler = Hit->Location - Start;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("321linetrace"))
		UKismetSystemLibrary::DrawDebugLine(GetWorld(), Start, End, FColor(100, 0, 0));
		UKismetSystemLibrary::DrawDebugSphere(GetWorld(), End, 5, 5, FLinearColor::White);
	}

	if (Ruler.Size() < HoverHeight)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorUpVector() * Speed * Time;
		SetActorLocation(NewLocation);
	}
	else
	{
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorUpVector() * Speed * -1 * Time;
		SetActorLocation(NewLocation);
	}
}
/*
RV_Hit.bBlockingHit //did hit something? (bool)
RV_Hit.GetActor(); //the hit actor if there is one
RV_Hit.ImpactPoint;  //FVector
RV_Hit.ImpactNormal;  //FVector
*/