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
	// Sets default values for this pawn's properties
	Aracing_gameGameModeBase();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category = "GameRules")
	int GetScore();

	UFUNCTION()
	void EnemyDied();

	UFUNCTION()
	void CoinAcquired();

	void SetGamePaused(bool bIsPaused);
	
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver();

	UFUNCTION()
	float CountdownTime();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> CountdownWidgetClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> ScoreWidgetClass;
	
	UPROPERTY(VisibleAnywhere)
	class UCountdownWidget* CountdownWidget;
	
	UPROPERTY(VisibleAnywhere)
	class UScoreCounter* ScoreCounter;
	
private:
	UPROPERTY(EditAnywhere, Category = "GameRules")
	int KillCounter = 0;

	UPROPERTY()
	bool bIsCountingDown = false;
	
	UPROPERTY(EditAnywhere, Category = "GameRules")
	int CoinCounter = 0;

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
	
};
