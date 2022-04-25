// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayerCar.h"
#include "SplineClass.h"
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

	FVector CarDirection = FVector(0.f, 0.f, 0.f);

	void LineTrace();
	float HoverHeight = 250;
	float WallCheck = 3500;
	float WallCheck2 = 500;
	float InterpSpeed = 0.5f;
	float InterpSpeed2 = 0.2f;
	FVector Ruler;
	FVector RulerRight;
	FVector RulerLeft;
	FVector WallImpact;
	FRotator SmoothRot;
	FRotator ROTTOT;
	FRotator MyRotator;
	FRotator MyRotator2;
	FRotator MyRotator3;
	FRotator MyRotator4;
	FRotator LastRotation;

	float AngleAxis;

	float RotationCheck;
	float Time;
	float Turn = 0.f;
	float Speed = 3;

private:

	UPROPERTY(EditAnywhere)
		float ForceStrength;
	UPROPERTY(EditAnywhere)
		float ForceStrength2;
	
};
