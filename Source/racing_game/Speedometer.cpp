// Fill out your copyright notice in the Description page of Project Settings.


#include "Speedometer.h"
#include "Components/ProgressBar.h"

void USpeedometer::SpeedUpdate()
{
	if (!OwnerCar->IsValidLowLevel())
		return;
	
	Speedometer->SetPercent(OwnerCar->GetSpeed());
}
