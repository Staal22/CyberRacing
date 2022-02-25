// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include"Components/StaticMeshComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	///A standard box collider with Overlap Events:
	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("MyEnemyCollider"));
	RootComponent = Root;
	Root->SetGenerateOverlapEvents(true);
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(Root);
	//Mesh is chosen in BP.

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
	Super::Tick(DeltaTime);

}

void AEnemy::IsHit()
{
	//destroys actor
	Destroy();
}

