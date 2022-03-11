// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCar.h"
#include "Blueprint/UserWidget.h"
#include "HealthBar.generated.h"


UCLASS()
class RACING_GAME_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetOwner(APlayerCar* InCar)
	{
		OwnerCar = InCar;
	}

protected:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentHealthLabel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxHealthLabel;

	TWeakObjectPtr<APlayerCar> OwnerCar;

public:
	UFUNCTION()
	void HealthUpdate();

	
};
