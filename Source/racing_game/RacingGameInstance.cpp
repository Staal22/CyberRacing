// Fill out your copyright notice in the Description page of Project Settings.


#include "RacingGameInstance.h"

bool URacingGameInstance::GetTimeAtkActive()
{
	return bTimeAttackActive;
}

UStaticMesh* URacingGameInstance::GetVehicleMesh()
{
	return VehicleMesh;
}
