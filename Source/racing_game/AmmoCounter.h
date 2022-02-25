// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerCar.h"
#include "AmmoCounter.generated.h"


UCLASS()
class RACING_GAME_API UAmmoCounter : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetOwnerShip(APlayerCar* InCar)
	{
		OwnerCar = InCar;
	}

protected:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* AmmoBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentAmmoLabel;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MaxAmmoLabel;

	TWeakObjectPtr<APlayerCar> OwnerCar;

public:
	UFUNCTION()
	void AmmoUpdate();

};
