// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include"Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "PlayerCar.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	///A standard box collider with Overlap Events:
	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("MyEnemyCollider"));
	SetRootComponent(Root);
	Root->SetGenerateOverlapEvents(true);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));	//apply in BP
	SkeletalMesh->SetupAttachment(Root);
	AIController = CreateDefaultSubobject<AAIController>(TEXT("EnemyAIController"));

	

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	MoveDirection = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - GetActorLocation();
	MoveDirection.Normalize();
	SetActorRotation(MoveDirection.Rotation());

	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	
	APlayerCar* PlayerCar = Cast<APlayerCar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	Super::Tick(DeltaTime);
	MoveDirection = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - GetActorLocation();
	MoveDirection.Normalize();
	SetActorRotation(MoveDirection.Rotation());
	Root->AddRelativeLocation(GetActorForwardVector()*Speed);

	AIController->AAIController::MoveToActor(PlayerCar, 1);
	
}

void AEnemy::IsHit()
{						//destroys actor
	//explosions fx
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionUponDeath, GetTransform(), true);
	//death sound
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());

	Destroy();
}

