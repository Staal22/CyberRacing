// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PlayerCar.h"
#include "AICar.generated.h"

UCLASS()
class RACING_GAME_API AAICar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAICar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// setting up mesh component and collision component for coin
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AICarMesh")
		UStaticMeshComponent* AICarMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AICarThings")
		class USphereComponent* Collision{};

	void LineTrace();
	float HoverHeight = 250;
	FHitResult* Hit = new FHitResult();
	FVector Start = GetActorLocation();
	FVector End = Start + FVector(0, 0, -HoverHeight);
	FVector Ruler;

	float Speed = 200;

};
