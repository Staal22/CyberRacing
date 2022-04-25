// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RacingGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class RACING_GAME_API URacingGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION()
	bool GetTimeAtkActive();

	UFUNCTION()
	UStaticMesh* GetVehicleMesh();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bTimeAttackActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* VehicleMesh;
};
