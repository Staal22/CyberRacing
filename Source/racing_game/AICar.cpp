// Fill out your copyright notice in the Description page of Project Settings.


#include "AICar.h"

// Sets default values
AAICar::AAICar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAICar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAICar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

