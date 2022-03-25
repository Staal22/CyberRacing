// Fill out your copyright notice in the Description page of Project Settings.


#include "CountdownWidget.h"
#include "racing_gameGameModeBase.h"

void UCountdownWidget::CountdownUpdate()
{
	RacingGameMode = Cast <Aracing_gameGameModeBase>(GetWorld()->GetAuthGameMode());

	if (!RacingGameMode)
		return;


	
}
