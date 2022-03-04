// Copyright Epic Games, Inc. All Rights Reserved.


#include "racing_gameGameModeBase.h"

int Aracing_gameGameModeBase::GetScore()
{
	return (KillCounter * 100 + CoinCounter * 1000);
}

void Aracing_gameGameModeBase::EnemyDied()
{
	KillCounter++;
}

void Aracing_gameGameModeBase::CoinAcquired()
{
	CoinCounter++;
}
