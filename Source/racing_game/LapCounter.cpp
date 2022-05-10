// Fill out your copyright notice in the Description page of Project Settings.


#include "LapCounter.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void ULapCounter::LapUpdate()
{
	RacingGameInstance = Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (!RacingGameInstance)
		return;

	FNumberFormattingOptions Opts;
	Opts.SetMaximumFractionalDigits(0);
	CurrentLap->SetText(FText::AsNumber(RacingGameInstance->GetLap(), &Opts));
	MaxLap->SetText(FText::AsNumber(RacingGameInstance->GetMaxLap(), &Opts));
}
