// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreCounter.h"
#include "racing_gameGameModeBase.h"
#include <Components/TextBlock.h>

void UScoreCounter::ScoreUpdate()
{
	RacingGameMode = Cast <Aracing_gameGameModeBase>(GetWorld()->GetAuthGameMode());

	if (!RacingGameMode)
		return;

	CurrentScore->SetText(FText::FromString(FString::Printf(TEXT("Score : %i"), RacingGameMode->GetScore())));
	KillCount->SetText(FText::FromString(FString::Printf(TEXT("Kills : %i"), RacingGameMode->GetKillCount())));
}
