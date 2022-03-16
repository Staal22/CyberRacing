// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCheckpointHitPlayerSignature, AActor*, PlayerHit);

UCLASS()
class RACING_GAME_API ACheckpoint : public AActor
{
	GENERATED_BODY()
	FCheckpointHitPlayerSignature OnCheckpointHitPlayer;

public:	
	// Sets default values for this actor's properties
	ACheckpoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CPMesh")
		UStaticMeshComponent* CPMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CPThings")
		class UBoxComponent* Collision{};

public:
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);
};
