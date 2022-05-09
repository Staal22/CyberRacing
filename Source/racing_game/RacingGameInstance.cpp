// Fill out your copyright notice in the Description page of Project Settings.


#include "RacingGameInstance.h"

FString URacingGameInstance::GetActiveMode()
{
	return ActiveMode;
}

UStaticMesh* URacingGameInstance::GetVehicleMesh()
{
	return VehicleMesh;
}

float URacingGameInstance::GetTAtkDifficulty()
{
	return TAtkDifficulty;
}

int URacingGameInstance::GetLap()
{
	return LapCounter;
}

int URacingGameInstance::GetMaxLap()
{
	return LapMax;
}
