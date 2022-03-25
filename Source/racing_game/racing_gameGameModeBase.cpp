// Copyright Epic Games, Inc. All Rights Reserved.


#include "racing_gameGameModeBase.h"
#include "CountdownWidget.h"
#include "ScoreCounter.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void Aracing_gameGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	const auto World = GetWorld();

	TimerDelegate.BindLambda([&]
	{
		bIsCountingDown = false;
		SetGamePaused(false);
	});
	bIsCountingDown = true;
	SetGamePaused(true);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 3.f, false);
	
	if (IsValid(ScoreWidgetClass))
		ScoreCounter = Cast<UScoreCounter>(CreateWidget(World, ScoreWidgetClass));
	ScoreCounter->SetDesiredSizeInViewport(FVector2D(100.f, 40.f));
	ScoreCounter->SetPositionInViewport(FVector2D(0.f, 0.f));
	ScoreCounter->AddToViewport();
	ScoreCounter->ScoreUpdate();

	if (IsValid(CountdownWidgetClass))
		CountdownWidget = Cast<UCountdownWidget>(CreateWidget(World, CountdownWidgetClass));
	CountdownWidget->SetDesiredSizeInViewport(FVector2D(100.f, 40.f));
	CountdownWidget->SetPositionInViewport(FVector2D(120.f, 120.f));
	CountdownWidget->AddToViewport();
	CountdownWidget->CountdownUpdate();
	
}

void Aracing_gameGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsCountingDown)
		CountdownWidget->CountdownUpdate();
	else if (CountdownWidget->IsInViewport())
		CountdownWidget->RemoveFromViewport();
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

float Aracing_gameGameModeBase::CountdownTime()
{
	if (3.f - GetWorld()->GetTimeSeconds() < 0.f)
		bIsCountingDown = false;
	return 3.f - GetWorld()->GetTimeSeconds();
}

void Aracing_gameGameModeBase::CoinAcquired()
{
	CoinCounter++;
	ScoreCounter->ScoreUpdate();
}

void Aracing_gameGameModeBase::SetGamePaused(bool bIsPaused)
{
	APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	APlayerCar* PlayerCar = Cast<APlayerCar>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	
	if (MyPlayer != nullptr)
	{
		if (bIsPaused == true)
			PlayerCar->DisableInput(MyPlayer);
		if (bIsPaused == false)
			PlayerCar->EnableInput(MyPlayer);
	}
}


