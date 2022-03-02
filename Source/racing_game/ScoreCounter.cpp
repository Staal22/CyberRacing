// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreCounter.h"
#include "racing_gameGameModeBase.h"
#include <Components/TextBlock.h>

void UScoreCounter::ScoreUpdate()
{
	if (!OwnerCar->IsValidLowLevel())
		return;

	RacingGameMode = Cast <Aracing_gameGameModeBase>(GetWorld()->GetAuthGameMode());

	CurrentScore->SetText(FText::FromString(FString::Printf(TEXT("Score : %i"), RacingGameMode->GetScore())));
}
