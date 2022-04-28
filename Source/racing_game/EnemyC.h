// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyC.generated.h"

UCLASS()
class RACING_GAME_API AEnemyC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyC();
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=AI)
	class AAIController* AIController{nullptr};

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=AI)
	class USphereComponent* PlayerSensingSphere{nullptr};

	 UPROPERTY(EditAnywhere, BlueprintReadOnly)
	 class UCapsuleComponent* Root {nullptr};
	//
	// UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// class USkeletalMeshComponent* SkeletalMesh {nullptr};

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex);
	UFUNCTION()
	void MoveToTarget(class APlayerCar* RefPlayerCar);
private:

	UPROPERTY(EditAnywhere)
	float MaxWalkSpeed;

	//DeathFX, init through blueprint
	UPROPERTY(EditAnywhere, Category = "EnemyFX")
	UParticleSystem* ExplosionUponDeath = nullptr;
    
	UPROPERTY(EditAnywhere, Category = "EnemyFX")
	USoundBase* DeathSound = nullptr;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void IsHit();
};
