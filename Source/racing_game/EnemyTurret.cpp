// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTurret.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include"Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyTurret::AEnemyTurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	///A standard box collider with Overlap Events:
	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("MyEnemyCollider"));
	SetRootComponent(Root);
	Root->SetGenerateOverlapEvents(true);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));	//apply in BP
	SkeletalMesh->SetupAttachment(Root);


}


void AEnemyTurret::IsHit()
{
	//explosions fx
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionUponDeath, GetTransform(), true);
	//death sound
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
	//removes actor from world
	Destroy();
}


// Called when the game starts or when spawned
void AEnemyTurret::BeginPlay()
{
	Super::BeginPlay();
	//rotates turret towards player
	RotationDirection = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - GetActorLocation();
	RotationDirection.Normalize();
	SetActorRotation(RotationDirection.Rotation());
}

void AEnemyTurret::Shoot()
{
	UWorld* World = GetWorld();
	FVector Location = GetActorLocation();
	Bullet = World->SpawnActor<ABullet>(BulletToSpawn, Location + GetActorForwardVector() * 100.f, GetActorRotation());
}
// Called every frame
void AEnemyTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotationDirection = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - GetActorLocation();
	RotationDirection.Normalize();
	SetActorRotation(RotationDirection.Rotation());
}

