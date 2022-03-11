// Copyright Epic Games, Inc. All Rights Reserved.


#include "racing_gameGameModeBase.h"
#include "ScoreCounter.h"
#include "Blueprint/UserWidget.h"

void Aracing_gameGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	const auto World = GetWorld();
	
	if (IsValid(ScoreWidgetClass))
		ScoreCounter = Cast<UScoreCounter>(CreateWidget(World, ScoreWidgetClass));
	ScoreCounter->SetDesiredSizeInViewport(FVector2D(100.f, 40.f));
	ScoreCounter->SetPositionInViewport(FVector2D(0.f, 0.f));
	ScoreCounter->AddToViewport();
	ScoreCounter->ScoreUpdate();
	
}


int Aracing_gameGameModeBase::GetScore()
{
	return (KillCounter * 100 + CoinCounter * 1000);
}

void Aracing_gameGameModeBase::EnemyDied()
{
	KillCounter++;
	ScoreCounter->ScoreUpdate();
}

void Aracing_gameGameModeBase::CoinAcquired()
{
	CoinCounter++;
	ScoreCounter->ScoreUpdate();
}


