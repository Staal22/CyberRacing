// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerCar.h"
#include "Speedometer.generated.h"


UCLASS()
class RACING_GAME_API USpeedometer : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetOwner(APlayerCar* InCar)
	{
		OwnerCar = InCar;
	}

protected:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* Speedometer;

	TWeakObjectPtr<APlayerCar> OwnerCar;
	
public:
	UFUNCTION()
	void SpeedUpdate();
	
};
