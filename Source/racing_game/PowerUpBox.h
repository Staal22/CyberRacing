// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "PowerUpBox.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPUBoxHitPlayerSignature, AActor*, BoxHit);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPUBDestroyedSignature);

UCLASS()
class RACING_GAME_API APowerUpBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerUpBox();

	FPUBoxHitPlayerSignature OnPUBoxHit;
	FPUBDestroyedSignature OnPUDestroyed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PUBMesh")
		UStaticMeshComponent* PUBMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PUBThings")
		class USphereComponent* Collision{};

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void Destruction();

	int randint;

	float Speed = 50.f;
	bool bounceUp = true;
	float bounceTime = 0.f;
	float Turn = 0.f;
};
