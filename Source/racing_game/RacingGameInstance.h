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
	FString GetActiveMode();

	UFUNCTION()
	UStaticMesh* GetVehicleMesh();

	UFUNCTION()
	float GetTAtkDifficulty();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString ActiveMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bTrueLap = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* VehicleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TAtkDifficulty = 15.f;
	
};
