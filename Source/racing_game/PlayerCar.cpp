// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCar.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include <Components/WidgetComponent.h>
#include "DrawDebugHelpers.h"


// Sets default values
APlayerCar::APlayerCar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	//SetRootComponent(Arrow);

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	SetRootComponent(PlayerMesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 1200;
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 5.f;
	SpringArm->SetupAttachment(PlayerMesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	AmmoComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	AmmoComp->SetupAttachment(GetRootComponent());

	Ammo = MaxAmmo;


}

// Called when the game starts or when spawned
void APlayerCar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UWorld* World = GetWorld();

	ForwardForce *= MoveSpeed;
	TurnForce *= TurnSpeed;
	PlayerMesh->AddRelativeRotation(FRotator(0.f, TurnForce, 0.f));
	DrawDebugLine(World, GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 15.f, FColor(255, 0, 0), false, 3.0f, 0.0f, 4.0f);
	PlayerMesh->AddRelativeLocation(GetActorForwardVector() * ForwardForce);
	/*PlayerMesh->AddRelativeLocation(FVector(ForwardForce, 0.f, 0.f) * MoveSpeed);*/


}

// Called to bind functionality to input
void APlayerCar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &APlayerCar::Drive);
	PlayerInputComponent->BindAxis("TurnL", this, &APlayerCar::Turn);


}

void APlayerCar::Drive(float Force)
{
	ForwardForce = Force;
}

void APlayerCar::Turn(float TurnDirection)
{
	TurnForce = TurnDirection;
}

void APlayerCar::Shoot()
{

}

float APlayerCar::GetAmmo()
{
	return Ammo;
}

float APlayerCar::GetMaxAmmo()
{
	return MaxAmmo;
}

