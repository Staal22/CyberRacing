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
	//down
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

	if (Ruler.Size() < HoverHeight-5)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorUpVector() * Speed * Time;
		SetActorLocation(NewLocation);
	}
	else if (Ruler.Size() > HoverHeight+5)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorUpVector() * Speed * -1 * Time;
		SetActorLocation(NewLocation);
	}

	//right
	FHitResult* Hit2 = new FHitResult();
	FVector End2 = Start + FVector(0, WallCheck, 0);
	GetWorld()->LineTraceSingleByChannel(*Hit2, Start, End2, ECC_Visibility); //ECC_Pawn
	if (Hit2)
	{
		UE_LOG(LogTemp, Warning, TEXT("Wallcheck"))
			UKismetSystemLibrary::DrawDebugLine(GetWorld(), Start, End2, FColor(100, 0, 0));
		UKismetSystemLibrary::DrawDebugSphere(GetWorld(), Hit2->Location, 5, 5, FLinearColor::Red);
		RulerSide = Hit2->Location - Start;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Checkwall"))
			UKismetSystemLibrary::DrawDebugLine(GetWorld(), Start, End2, FColor(100, 0, 0));
		UKismetSystemLibrary::DrawDebugSphere(GetWorld(), End2, 5, 5, FLinearColor::White);
	}

	//left
	FHitResult* Hit3 = new FHitResult();
	FVector End3 = Start + FVector(0, -WallCheck, 0);
	GetWorld()->LineTraceSingleByChannel(*Hit3, Start, End3, ECC_Visibility); //ECC_Pawn
	if (Hit3)
	{
		UE_LOG(LogTemp, Warning, TEXT("Wallcheck"))
			UKismetSystemLibrary::DrawDebugLine(GetWorld(), Start, End3, FColor(100, 0, 0));
		UKismetSystemLibrary::DrawDebugSphere(GetWorld(), Hit3->Location, 5, 5, FLinearColor::Red);
		RulerSide = Hit3->Location - Start;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Checkwall"))
			UKismetSystemLibrary::DrawDebugLine(GetWorld(), Start, End3, FColor(100, 0, 0));
		UKismetSystemLibrary::DrawDebugSphere(GetWorld(), End3, 5, 5, FLinearColor::White);
	}
}
/*
RV_Hit.bBlockingHit //did hit something? (bool)
RV_Hit.GetActor(); //the hit actor if there is one
RV_Hit.ImpactPoint;  //FVector
RV_Hit.ImpactNormal;  //FVector
*/