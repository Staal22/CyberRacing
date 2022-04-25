// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterDisplay.generated.h"
USTRUCT(BlueprintType)
struct FCharacterVehicle
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString MoreInfo;
};

UCLASS()
class RACING_GAME_API ACharacterDisplay : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ACharacterDisplay();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* DisplayMesh = nullptr;

	UFUNCTION(BlueprintCallable)
	void ChangeCharacter();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* Character1Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* Character2Mesh;

	UPROPERTY(BlueprintReadOnly)
	TArray<FCharacterVehicle> Characters;

	UPROPERTY(BlueprintReadOnly)
	int CharacterIndex = 0;
private:
	bool bBounceUp = true;
	
	float BounceTime = 0.f;
	
	float Turn = 0.f;

	float Speed = 50.f;
	
};
