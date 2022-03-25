// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyC.h"

#include "AIController.h"
#include"Gameframework/MovementComponent.h"
#include"Kismet/KismetSystemLibrary.h"
#include"PlayerCar.h"
#include "Components/SphereComponent.h"

// Sets default values
AEnemyC::AEnemyC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerSensingSphere=CreateDefaultSubobject<USphereComponent>(TEXT("PlayerSensingSphere"));
	AIController=Cast<AAIController>(GetController());
}



// Called when the game starts or when spawned
void AEnemyC::BeginPlay()
{
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


void AEnemyC::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// APlayerCar* PlayerCar=Cast<APlayerCar>(OtherActor);
	// if(PlayerCar)
	// {
	// 	PlayerCar->SetEnemy(this);
	// }
}

void AEnemyC::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                           UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex)
{
}
