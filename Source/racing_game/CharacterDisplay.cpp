// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterDisplay.h"

// Sets default values
ACharacterDisplay::ACharacterDisplay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DisplayMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DisplayMesh"));
}

// Called when the game starts or when spawned
void ACharacterDisplay::BeginPlay()
{
	Super::BeginPlay();

	if (Character1 != nullptr)
		DisplayMesh->SetStaticMesh(Character1);
}

// Called every frame
void ACharacterDisplay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	
}

