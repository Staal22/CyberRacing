 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerCar.h"
#include "ScoreCounter.generated.h"


UCLASS()
class RACING_GAME_API UScoreCounter : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetOwner(APlayerCar* InCar)
	{
		OwnerCar = InCar;
	}

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentScore;

	TWeakObjectPtr<APlayerCar> OwnerCar;

private:
	UPROPERTY()
	class Aracing_gameGameModeBase* RacingGameMode;

public:
	UFUNCTION()
	void ScoreUpdate();


};
