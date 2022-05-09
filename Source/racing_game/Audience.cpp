// Fill out your copyright notice in the Description page of Project Settings.


#include "Audience.h"
#include "racing_gameGameModeBase.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"

// Sets default values
AAudience::AAudience()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(Collision);

	AudienceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AudienceMesh"));
	AudienceMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AAudience::BeginPlay()
{
	Super::BeginPlay();
	randFloat = FMath::RandRange(0, 1);
	Dance = randFloat;
	bounceTime = randFloat;
	
	const auto World = GetWorld();
	RacingGameMode = Cast<Aracing_gameGameModeBase>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void AAudience::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Dance += DeltaTime;
	bounceTime += DeltaTime;

	if (bounceTime < 0.5f)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorUpVector() * Speed * DeltaTime;
		SetActorLocation(NewLocation);
	}
	if (Dance < 0.5f)
	{
		Collision->SetRelativeRotation(FRotator(Dance * 60.f, 90.f, 0.f));
	}
	if (bounceTime > 0.5f && bounceTime < 1.f)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorUpVector() * Speed * -1 * DeltaTime;
		SetActorLocation(NewLocation);
		//UE_LOG(LogTemp, Warning, TEXT(" "));
	}
	if (Dance > 0.5f && Dance < 1.f)
	{
		Collision->SetRelativeRotation(FRotator(60.f - Dance * 60.f, 90.f, 0.f));
	}
	if (bounceTime > 1.0f && bounceTime < 1.5f)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorUpVector() * Speed * DeltaTime;
		SetActorLocation(NewLocation);
	}
	if (Dance > 1.f && Dance < 1.5f)
	{
		Collision->SetRelativeRotation(FRotator(60.f - Dance * 60.f, 90.f, 0.f));
	}
	if (bounceTime > 1.5f && bounceTime < 2.f)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorUpVector() * Speed * -1 * DeltaTime;
		SetActorLocation(NewLocation);
		//UE_LOG(LogTemp, Warning, TEXT(" "));
	}
	if (Dance > 1.5f && Dance < 2.0f)
	{
		Collision->SetRelativeRotation(FRotator(-120.f + Dance * 60.f, 90.f, 0.f));
	}

	if (bounceTime > 2.0f)
	{
		bounceTime = 0.f;
	}

	if (Dance > 2.0f)
	{
		Dance = 0.f;
	}
	
}

