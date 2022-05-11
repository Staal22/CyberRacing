// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpDisplay.h"
#include "PlayerCar.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"

void UPowerUpDisplay::PuImageUpdate()
{
	const UWorld* World = GetWorld();
	if (World)
	{
		PlayerCar = Cast<APlayerCar>(UGameplayStatics::GetPlayerPawn(World, 0));
	}
	
	if (!PlayerCar)
		return;

	const FString MinePath = FString("/Game/Textures/Icons/Legend/mine.mine");
	const FString MissilePath = FString("/Game/Textures/Icons/Legend/missile.missile");
	UTexture2D* MineTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *MinePath));
	UTexture2D* MissileTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *MissilePath));

	if (PlayerCar->GetPU() == 0)
		Powerup->SetVisibility(ESlateVisibility::Hidden);

	else if (PlayerCar->GetPU() == 1)
	{
		Powerup->SetVisibility(ESlateVisibility::Visible);
		Powerup->SetBrushFromTexture(MissileTexture);
	}

	else if (PlayerCar->GetPU() == 2)
	{
		Powerup->SetVisibility(ESlateVisibility::Visible);
		Powerup->SetBrushFromTexture(MineTexture);
	}

	if (PlayerCar->ShotgunActive() == false)
		Shotgun->SetVisibility(ESlateVisibility::Hidden);

	if (PlayerCar->ShotgunActive() == true)
	{
		Shotgun->SetVisibility(ESlateVisibility::Visible);
		
	}
}
