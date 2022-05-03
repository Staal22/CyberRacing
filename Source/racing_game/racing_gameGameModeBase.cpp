// Copyright Epic Games, Inc. All Rights Reserved.


#include "racing_gameGameModeBase.h"
#include "CountdownWidget.h"
#include "RacingGameInstance.h"
#include "ScoreCounter.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


Aracing_gameGameModeBase::Aracing_gameGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void Aracing_gameGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	const auto World = GetWorld();
	
	SetGamePaused(true, false);

	RacingGameInstance = Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(World));
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 3.f, false);

	if (IsValid(ScoreWidgetClass))
		ScoreCounter = Cast<UScoreCounter>(CreateWidget(World, ScoreWidgetClass));
	ScoreCounter->SetDesiredSizeInViewport(FVector2D(100.f, 40.f));
	ScoreCounter->SetPositionInViewport(FVector2D(0.f, 100.f));
	if (RacingGameInstance->GetActiveMode() == "Horde")
	{
		ScoreCounter->AddToViewport();
		ScoreCounter->ScoreUpdate();
	}

	if (IsValid(CountdownWidgetClass))
		CountdownWidget = Cast<UCountdownWidget>(CreateWidget(World, CountdownWidgetClass));
	// CountdownWidget->SetDesiredSizeInViewport(FVector2D(100.f, 40.f));
	// CountdownWidget->SetPositionInViewport(FVector2D(550.f, 120.f));
	// CountdownWidget->SetPositionInViewport(FVector2D());
	CountdownWidget->AddToViewport();
	CountdownWidget->CountdownUpdate();
	
}

void Aracing_gameGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CountdownWidget->CountdownUpdate();
}

int Aracing_gameGameModeBase::GetScore()
{
	return Score;
}

int Aracing_gameGameModeBase::GetKillCount()
{
	return KillCounter;
}

void Aracing_gameGameModeBase::EnemyDied()
{
	KillCounter++;
	Score += 100;
	ScoreUpdate();
}

float Aracing_gameGameModeBase::GetDifficulty(FString Parameter)
{
	float ReturnValue;
	if (Parameter == "Timer")
	{
		ReturnValue = RacingGameInstance->GetTAtkDifficulty();
	}
	else
	{
		ReturnValue = 0.f;
	}
	return ReturnValue;
}

float Aracing_gameGameModeBase::CountdownTime()
{
	if (3.6f - GetWorld()->GetTimeSeconds() < 0.6f)
	{
		bInitialCountDown = false;
		SetGamePaused(false, false);
	}
	return 3.6f - GetWorld()->GetTimeSeconds();
}

bool Aracing_gameGameModeBase::IsStarting()
{
	return bInitialCountDown;
}

void Aracing_gameGameModeBase::ScoreUpdate()
{
	ScoreCounter->ScoreUpdate();
}

void Aracing_gameGameModeBase::CoinAcquired()
{
	CoinCounter++;
	Score += 1000;
	ScoreUpdate();
}

void Aracing_gameGameModeBase::AddScore(int ScoreToAdd)
{
	Score += ScoreToAdd;
}

void Aracing_gameGameModeBase::SetGamePaused(bool bIsPaused, bool bTruePause)
{
	APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	APlayerCar* PlayerCar = Cast<APlayerCar>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	const auto World = GetWorld();
	
	if (MyPlayer != nullptr)
	{
		if (bIsPaused == true)
		{
			if (bTruePause == true)
			{
				UGameplayStatics::SetGamePaused(World, true);
			}
			else
			{
				PlayerCar->DisableInput(MyPlayer);
			}
		}
		else if (bIsPaused == false)
		{
			UGameplayStatics::SetGamePaused(World, false);
			PlayerCar->EnableInput(MyPlayer);
		}
	}
}


