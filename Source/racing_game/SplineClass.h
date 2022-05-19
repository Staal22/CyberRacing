// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Components/BoxComponent.h"
#include "SplineClass.generated.h"

UCLASS()
class RACING_GAME_API ASplineClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplineClass();

	void OnConstruction(const FTransform& Transform) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	UPROPERTY(VisibleAnywhere, Category = "Spline")
	USplineComponent* SplineComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	UStaticMesh* SplineMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoinThings")
	class UBoxComponent* Collision{};

	//making it easy changing axis in viewport
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
		TEnumAsByte<ESplineMeshAxis::Type> ForwardAxis;

	UPROPERTY()
		TArray<USplineMeshComponent*> MeshComponents;

};
