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

	AngleAxis = 0;

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

	AICarMesh->SetRelativeRotation(FRotator(0.f, Turn, 0.f));

	FVector NewLocation = GetActorLocation();
	FVector Radius = GetActorLocation() + FVector(200, 0, 0);
	FVector RotateValue = Radius.RotateAngleAxis(AngleAxis, FVector(0, 0, 1));

	NewLocation.X += RotateValue.X;
	NewLocation.Y += RotateValue.Y;
	NewLocation.Z += RotateValue.Z;

	SetActorLocation(NewLocation);

	//FVector NewLocation = GetActorLocation();
	//NewLocation += GetActorForwardVector() * Speed;
	//SetActorLocation(NewLocation);

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
	Ruler = Hit->Location - Start;
	if (Hit)
	{
		UE_LOG(LogTemp, Warning, TEXT("123linetrace"))
		UKismetSystemLibrary::DrawDebugLine(GetWorld(), Start, End, FColor(100, 0, 0));
		UKismetSystemLibrary::DrawDebugSphere(GetWorld(), Hit->Location, 5, 5, FLinearColor::Red);
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
		NewLocation += GetActorUpVector() * Speed;
		SetActorLocation(NewLocation);
	}
	else if (Ruler.Size() > HoverHeight+5)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorUpVector() * Speed * -1;
		SetActorLocation(NewLocation);
	}

	//right
	FHitResult* Hit2 = new FHitResult();
	FVector End2 = Start + FVector(0, WallCheck, 0);
	GetWorld()->LineTraceSingleByChannel(*Hit2, Start, End2, ECC_Visibility); //ECC_Pawn
	RulerRight = Hit2->Location - Start;
	if (Hit2)
	{
		UE_LOG(LogTemp, Warning, TEXT("Wallcheck"))
			UKismetSystemLibrary::DrawDebugLine(GetWorld(), Start, End2, FColor(100, 0, 0));
		UKismetSystemLibrary::DrawDebugSphere(GetWorld(), Hit2->Location, 5, 5, FLinearColor::Red);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Checkwall"))
			UKismetSystemLibrary::DrawDebugLine(GetWorld(), Start, End2, FColor(100, 0, 0));
		UKismetSystemLibrary::DrawDebugSphere(GetWorld(), End2, 5, 5, FLinearColor::White);
	}

	if (RulerRight.Size() < WallCheck)
	{
		UE_LOG(LogTemp, Warning, TEXT("Left"))
		AngleAxis--;
	}
	if (RulerRight.Size() > WallCheck2)
	{
		UE_LOG(LogTemp, Warning, TEXT("Right"))
		AngleAxis++;
	}

	/*//left
	FHitResult* Hit3 = new FHitResult();
	FVector Start2 = GetActorLocation();
	FVector End3 = Start2 + FVector(0, WallCheck2, 0);
	GetWorld()->LineTraceSingleByChannel(*Hit3, Start2, End3, ECC_Visibility); //ECC_Pawn
	if (Hit3)
	{
		UE_LOG(LogTemp, Warning, TEXT("Wallcheck"))
			UKismetSystemLibrary::DrawDebugLine(GetWorld(), Start2, End3, FColor(100, 0, 0));
		UKismetSystemLibrary::DrawDebugSphere(GetWorld(), Hit3->Location, 5, 5, FLinearColor::Red);
		RulerLeft = Hit3->Location - Start2;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Checkwall"))
			UKismetSystemLibrary::DrawDebugLine(GetWorld(), Start2, End3, FColor(100, 0, 0));
		UKismetSystemLibrary::DrawDebugSphere(GetWorld(), End3, 5, 5, FLinearColor::White);
	}

	if (RulerLeft.Size() < WallCheck)
	{
		Turn = 90.f;
	}
	*/
}
/*
RV_Hit.bBlockingHit //did hit something? (bool)
RV_Hit.GetActor(); //the hit actor if there is one
RV_Hit.ImpactPoint;  //FVector
RV_Hit.ImpactNormal;  //FVector
*/