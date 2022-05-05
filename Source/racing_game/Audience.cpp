// Fill out your copyright notice in the Description page of Project Settings.


#include "Audience.h"
#include "racing_gameGameModeBase.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
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
	
	const auto World = GetWorld();
	RacingGameMode = Cast<Aracing_gameGameModeBase>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void AAudience::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Dance += DeltaTime;
	bounceTime += DeltaTime;

	if (bounceTime < 0.5f && bounceUp == true)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorUpVector() * Speed * DeltaTime;
		SetActorLocation(NewLocation);
	}
	if (bounceTime > 0.5f && bounceUp == true)
	{
		bounceUp = false;
		bounceTime = 0.f;
	}
	if (bounceTime < 0.5f && bounceUp == false)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorUpVector() * Speed * -1 * DeltaTime;
		SetActorLocation(NewLocation);
		//UE_LOG(LogTemp, Warning, TEXT(" "));
	}
	if (bounceTime > 0.5f && bounceUp == false)
	{
		bounceUp = true;
		bounceTime = 0.f;
	}

	if (Dance > 2.0f)
	{
		Dance = 0.f;
	}
	if (Dance < 0.5f)
	{
		AudienceMesh->SetRelativeRotation(FRotator(Dance * 60.f, 0.f, 0.f));
	}
	if (Dance > 0.5f && Dance < 1.f)
	{
		AudienceMesh->SetRelativeRotation(FRotator(45.f - Dance * 45.f, 0.f, 0.f));
	}
	if (Dance > 1.f && Dance < 1.5f)
	{
		AudienceMesh->SetRelativeRotation(FRotator(60.f - Dance * 60.f, 0.f, 0.f));
	}
	if (Dance > 1.5f && Dance < 2.0f)
	{
		AudienceMesh->SetRelativeRotation(FRotator(-120.f + Dance * 60.f, 0.f, 0.f));
	}
	
}

