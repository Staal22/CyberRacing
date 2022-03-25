// Fill out your copyright notice in the Description page of Project Settings.


#include "CountdownWidget.h"
#include "racing_gameGameModeBase.h"
#include "Components/TextBlock.h"

void UCountdownWidget::CountdownUpdate()
{
	RacingGameMode = Cast <Aracing_gameGameModeBase>(GetWorld()->GetAuthGameMode());

	if (!RacingGameMode)
		return;

	CurrentCount->SetText(FText::FromString(FString::Printf(TEXT("%f"), RacingGameMode->CountdownTime())));
	
}
