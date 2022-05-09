// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Audience.generated.h"

UCLASS()
class RACING_GAME_API AAudience : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAudience();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AudienceMesh")
		UStaticMeshComponent* AudienceMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AudienceThings")
		class USphereComponent* Collision{};

	float Dance = 0.f;
	float randFloat;
	float Speed = 1000.f;
	bool bounceUp = true;
	float bounceTime = 0.f;

private:
	UPROPERTY()
		class Aracing_gameGameModeBase* RacingGameMode;
};
