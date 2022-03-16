// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "racing_gameGameModeBase.generated.h"


UCLASS()
class RACING_GAME_API Aracing_gameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "GameRules")
	int GetScore();

	UFUNCTION()
	void EnemyDied();

	UFUNCTION()
	void CoinAcquired();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> ScoreWidgetClass;

	UPROPERTY(VisibleAnywhere)
	class UScoreCounter* ScoreCounter;
	
private:
	UPROPERTY(EditAnywhere, Category = "GameRules")
	int KillCounter = 0;

	UPROPERTY(EditAnywhere, Category = "GameRules")
	int CoinCounter = 0;

};
