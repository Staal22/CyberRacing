// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RacingGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "LapCounter.generated.h"

/**
 * 
 */
UCLASS()
class RACING_GAME_API ULapCounter : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentLap;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxLap;

private:
	UPROPERTY()
	URacingGameInstance* RacingGameInstance;

public:
	UFUNCTION(BlueprintCallable)
	void LapUpdate();
	
};
