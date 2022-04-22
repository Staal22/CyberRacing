// Fill out your copyright notice in the Description page of Project Settings.


#include "AICar.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AAICar::AAICar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(Collision);

	AICarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AICarMesh"));
	AICarMesh->SetupAttachment(GetRootComponent());

	ForceStrength = 20000.0f;
}

// Called when the game starts or when spawned
void AAICar::BeginPlay()
{
	Super::BeginPlay();

	SmoothRot = GetActorRotation();
}

// Called every frame 
void AAICar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LineTrace();
	Time += DeltaTime;

	/*
	FVector NewLocation = GetActorLocation();
	NewLocation += Collision->GetForwardVector() * Speed;
	SetActorLocation(NewLocation);
	*/

	FVector Forward = Collision->GetForwardVector();

	AICarMesh->AddForce(Forward * FMath::FInterpTo(0.0f, ForceStrength, Time, InterpSpeed2) * AICarMesh->GetMass());

	Collision->SetWorldRotation(FMath::RInterpTo(ROTTOT, MyRotator, Time, InterpSpeed));

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
	/*
	if (Ruler.Size() < HoverHeight-5)
	{
		FVector Up = AICarMesh->GetUpVector();

		AICarMesh->AddForce(Up * ForceStrength * AICarMesh->GetMass());
	}
	else if (Ruler.Size() > HoverHeight+5)
	{
		
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorUpVector() * Speed * -1;
		SetActorLocation(NewLocation);
		
	
	}
	*/
	
	//turn
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	FHitResult* Hit2 = new FHitResult();
	FVector End2 = Start + Collision->GetRightVector()*WallCheck;
	GetWorld()->LineTraceSingleByChannel(*Hit2, Start, End2, ECC_Visibility, Params); //ECC_Pawn
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

	//impact normal
	/*Hit2->ImpactNormal
		AICarMesh->GetUpVector()*/
	//FRotator MyRotator = FRotationMatrix::MakeFromZY(AICarMesh->GetUpVector(), Hit2->ImpactNormal).Rotator();
	//FRotator NewRot = UKismetMathLibrary::MakeRotFromYZ(-Hit2->ImpactNormal, Collision->GetUpVector());
	MyRotator = FRotationMatrix::MakeFromYZ(-Hit2->ImpactNormal, AICarMesh->GetUpVector()).Rotator();
	MyRotator.Pitch = 0;
	MyRotator.Roll = 0;
	MyRotator.Yaw -= 1;
	ROTTOT = AICarMesh->GetRelativeRotation();
}
