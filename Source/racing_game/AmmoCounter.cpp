// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoCounter.h"
#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>

void UAmmoCounter::AmmoUpdate()
{
	if (!OwnerCar->IsValidLowLevel())
		return;

	AmmoBar->SetPercent(OwnerCar->GetAmmo() / OwnerCar->GetMaxAmmo());

	FNumberFormattingOptions Opts;
	Opts.SetMaximumFractionalDigits(0);
	CurrentAmmoLabel->SetText(FText::AsNumber(OwnerCar->GetAmmo(), &Opts));
	MaxAmmoLabel->SetText(FText::AsNumber(OwnerCar->GetMaxAmmo(), &Opts));

}
