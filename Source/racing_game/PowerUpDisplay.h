// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PowerUpDisplay.generated.h"

/**
 * 
 */
UCLASS()
class RACING_GAME_API UPowerUpDisplay : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void PuImageUpdate();
	
protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* Powerup;

	UPROPERTY(meta = (BindWidget))
	UImage* Shotgun;

private:
	UPROPERTY()
	class APlayerCar* PlayerCar;
	
};
