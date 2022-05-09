// Fill out your copyright notice in the Description page of Project Settings.


#include "CountdownWidget.h"

#include "PlayerCar.h"
#include "racing_gameGameModeBase.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UCountdownWidget::CountdownUpdate()
{
	const UWorld* World = GetWorld();
	if (World)
	{
		RacingGameMode = Cast <Aracing_gameGameModeBase>(GetWorld()->GetAuthGameMode());
		PlayerCar = Cast<APlayerCar>(UGameplayStatics::GetPlayerPawn(World, 0));
	}
	
	if (!RacingGameMode)
		return;

	FNumberFormattingOptions Opts;
	Opts.SetMaximumFractionalDigits(0);
	
	if (RacingGameMode->IsStarting() == true)
	{
		StartCount->SetText(FText::AsNumber(RacingGameMode->CountdownTime(), &Opts));
	}
	else
	{
		if (StartCount->GetVisibility() != ESlateVisibility::Hidden)
		{
			StartCount->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	
	if (PlayerCar)
		TAtkCount->SetText(FText::AsNumber(PlayerCar->GetTAtkTime(), &Opts));
}