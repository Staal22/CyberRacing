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

public:
	UFUNCTION(BlueprintCallable, Category = "GameRules")
	int GetScore();

	UFUNCTION()
	void EnemyDied();

	UFUNCTION()
	float GetDifficulty(FString Parameter);

	UFUNCTION()
	void CoinAcquired();

	UFUNCTION()
	void AddScore(int ScoreToAdd);

	UFUNCTION()
	void SetGamePaused(bool bIsPaused);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void GameOver(const FString& Cause);

	UFUNCTION()
	float CountdownTime();

	UFUNCTION()
	bool IsStarting();

	UFUNCTION()
	void ScoreUpdate();
	
	bool bInitialCountDown = true;
	
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

	UPROPERTY(BlueprintReadOnly)
	int Score = 0;

	UPROPERTY(BlueprintReadOnly)
	int KillCounter = 0;
	
private:
	UPROPERTY()
	int CoinCounter = 0;
	
	UPROPERTY()
	class URacingGameInstance* RacingGameInstance;
	
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
	
};
