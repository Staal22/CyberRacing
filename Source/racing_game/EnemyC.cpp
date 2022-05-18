// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyC.h"

#include "AIController.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include"Kismet/KismetSystemLibrary.h"
#include"PlayerCar.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AEnemyC::AEnemyC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	///A standard box collider with Overlap Events:
	PlayerSensingSphere=CreateDefaultSubobject<USphereComponent>(TEXT("PlayerSensingSphere"));
	PlayerSensingSphere->SetupAttachment(GetRootComponent());
	PlayerSensingSphere->InitSphereRadius(3000.f);
	GetCharacterMovement()->MaxWalkSpeed = 450.f;//set max-walkspeed
}

// Called when the game starts or when spawned
void AEnemyC::BeginPlay()
{
	AIController=Cast<AAIController>(GetController());
	Super::BeginPlay();
	PlayerSensingSphere->OnComponentBeginOverlap.AddDynamic(this,&AEnemyC::OnOverlap);
	PlayerSensingSphere->OnComponentEndOverlap.AddDynamic(this,&AEnemyC::OnEndOverlap);
}

// Called every frame
void AEnemyC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemyC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyC::IsHit()
{
	//explosions fx
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionUponDeath, GetTransform(), true);
	//death sound
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
	//remove actor
	Destroy();
}


void AEnemyC::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                        UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCar* RefPlayerCar = Cast<APlayerCar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if(RefPlayerCar)
	{
		MoveToTarget(RefPlayerCar);
	}
}

void AEnemyC::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                           UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex)
{
	APlayerCar* RefPlayerCar = Cast<APlayerCar>(OtherActor);
	if (AIController && RefPlayerCar)
	{
		
		UE_LOG(LogTemp, Warning, TEXT("Player Ends Overlap"));
		AIController->StopMovement();
	}
}

void AEnemyC::MoveToTarget(APlayerCar* RefPlayerCar)
{
	
	if (AIController&&RefPlayerCar)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Overlaps"));

		
		FAIMoveRequest AIMoverequest;
		AIMoverequest.SetGoalActor(RefPlayerCar);	//Goal
		AIMoverequest.SetAcceptanceRadius(0.f);	//How close before stop
	
		FNavPathSharedPtr NavPath;	//Contains nodes for pathing
	
		AIController->MoveTo(AIMoverequest, &NavPath);
	}
}
