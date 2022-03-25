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
	
}

// Called every frame
void AAICar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LineTrace();
	FHitResult RV_Hit(ForceInit);
	if (RV_Hit.bBlockingHit == true)
	{
		{
			if (Ruler.Z < HoverHeight)
			{
				FVector NewLocation = GetActorLocation();
				NewLocation += GetActorUpVector() * Speed * DeltaTime;
				SetActorLocation(NewLocation);
			}
			else if (Ruler.Z > HoverHeight)
			{
				FVector NewLocation = GetActorLocation();
				NewLocation += GetActorForwardVector() * Speed * -1 * DeltaTime;
				SetActorLocation(NewLocation);
			}
			
		}
	}
}

void AAICar::LineTrace()
{
	//Re-initialize hit info
	//call GetWorld() from within an actor extending class
	GetWorld()->LineTraceSingleByChannel(*Hit, Start, End, ECC_Visibility); //ECC_Pawn
	if (Hit)
	{
		UKismetSystemLibrary::DrawDebugLine(GetWorld(), Start, End, FColor(100, 0, 0));
		UKismetSystemLibrary::DrawDebugSphere(GetWorld(), Hit->Location, 5, 5, FLinearColor::Red);
		Ruler = Hit->Location;
	}
	else
	{
		UKismetSystemLibrary::DrawDebugLine(GetWorld(), Start, End, FColor(100, 0, 0));
		UKismetSystemLibrary::DrawDebugSphere(GetWorld(), End, 5, 5, FLinearColor::White);
	}
}
/*
RV_Hit.bBlockingHit //did hit something? (bool)
RV_Hit.GetActor(); //the hit actor if there is one
RV_Hit.ImpactPoint;  //FVector
RV_Hit.ImpactNormal;  //FVector
*/