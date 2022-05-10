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

	UFUNCTION()
	int GetLap();

	UFUNCTION()
	int GetMaxLap();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ActiveMode = "Race";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor MaterialColor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bTrueLap = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bAITrueLap = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* VehicleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TAtkDifficulty = 120.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LapCounter = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AILapCounter = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LapMax = 3;
	
};
