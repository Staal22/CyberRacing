// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineClass.h"

// Sets default values
ASplineClass::ASplineClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>("Spline");
	if (SplineComponent)
	{
		SetRootComponent(SplineComponent);
	}
}

void ASplineClass::OnConstruction(const FTransform& Transform)
{
	if (!SplineMesh)
	{
		return;
	}

	for (int SplineCount = 0; SplineCount < (SplineComponent->GetNumberOfSplinePoints() - 1); SplineCount++)
	{
		USplineMeshComponent* SplineMeshComponent = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());

		SplineMeshComponent->SetStaticMesh(SplineMesh);
		SplineMeshComponent->SetMobility(EComponentMobility::Movable);
		SplineMeshComponent->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		SplineMeshComponent->RegisterComponentWithWorld(GetWorld());
		SplineMeshComponent->AttachToComponent(SplineComponent, FAttachmentTransformRules::KeepRelativeTransform);

		const FVector StartPoint = SplineComponent->GetLocationAtSplinePoint(SplineCount, ESplineCoordinateSpace::Local);
		const FVector StartTangent = SplineComponent->GetTangentAtSplinePoint(SplineCount, ESplineCoordinateSpace::Local);
		const FVector EndPoint = SplineComponent->GetLocationAtSplinePoint(SplineCount + 1, ESplineCoordinateSpace::Local);
		const FVector EndTangent = SplineComponent->GetTangentAtSplinePoint(SplineCount + 1, ESplineCoordinateSpace::Local);

		SplineMeshComponent->SetStartAndEnd(StartPoint, StartTangent, EndPoint, EndTangent, true);

		//SplineMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		SplineMeshComponent->SetForwardAxis(ForwardAxis);
	}
} 

// Called when the game starts or when spawned
void ASplineClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASplineClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

