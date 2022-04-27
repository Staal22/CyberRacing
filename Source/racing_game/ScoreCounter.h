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

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentScore;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* KillCount;

private:
	UPROPERTY()
	Aracing_gameGameModeBase* RacingGameMode;

public:
	UFUNCTION()
	void ScoreUpdate();
	
};
