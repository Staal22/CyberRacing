// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCar.generated.h"

UCLASS()
class RACING_GAME_API APlayerCar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCar")
	//UArrowComponent* Arrow = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCar")
	class UStaticMeshComponent* PlayerMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	class UCameraComponent* Camera = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	class USpringArmComponent* SpringArm = nullptr;

	UFUNCTION()
	void Drive(float Force);

	UFUNCTION()
	void Turn(float TurnDirection);

	UFUNCTION()
	void Shoot();

	UFUNCTION()
	float GetAmmo();

	UFUNCTION()
	float GetMaxAmmo();

protected:
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* AmmoComp;

private:
	UPROPERTY()
	float MoveSpeed = 15.f;

	UPROPERTY()
	float TurnSpeed = 2.f;

	UPROPERTY()
	float ForwardForce = 0.f;

	UPROPERTY()
	float TurnForce = 0.f;

	UPROPERTY()
	int Ammo = 0;

	UPROPERTY()
	int MaxAmmo = 20;

};
