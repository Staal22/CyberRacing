// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterDisplay.h"

// Sets default values
ACharacterDisplay::ACharacterDisplay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DisplayMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DisplayMesh"));

	Characters.Emplace();
	Characters.Emplace();

	//Hover Car
	Characters[0].Mesh = Character1Mesh;
	Characters[0].Name = "Hover Car";
	Characters[0].MoreInfo = "It go fast";

	//cone boi (waiting for jet)
	Characters[1].Mesh = Character2Mesh;
	Characters[1].Name = "Cone (placeholder)";
	Characters[1].MoreInfo = "Very nice to look at";
}

// Called when the game starts or when spawned
void ACharacterDisplay::BeginPlay()
{
	Super::BeginPlay();
	
	// DisplayMesh->SetStaticMesh(Characters[CharacterIndex].Mesh);
	DisplayMesh->SetStaticMesh(Character1Mesh);
}

// Called every frame
void ACharacterDisplay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//Modified from Sander's Shotgun code
	BounceTime += DeltaTime;
	if (BounceTime < 1.f && bBounceUp == true)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorUpVector() * Speed * DeltaTime;
		SetActorLocation(NewLocation);
	}
	if (BounceTime > 1.f && bBounceUp == true)
	{
		bBounceUp = false;
		BounceTime = 0.f;
	}
	if (BounceTime < 1.f && bBounceUp == false)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorUpVector() * Speed * -1 * DeltaTime;
		SetActorLocation(NewLocation);
		//UE_LOG(LogTemp, Warning, TEXT(" "));
	}
	if (BounceTime > 1.f && bBounceUp == false)
	{
		bBounceUp = true;
		BounceTime = 0.f;
	}

	Turn += DeltaTime;
	if (Turn > 9.f)
	{
		Turn = 0.f;
	}

	DisplayMesh->SetRelativeRotation(FRotator(0.f, Turn*40, 0.f));
}

void ACharacterDisplay::ChangeCharacter()
{
	CharacterIndex++;
	if (CharacterIndex >= Characters.Num())
	{
		CharacterIndex = 0;
	}
	// DisplayMesh->SetStaticMesh(Characters[CharacterIndex].Mesh);
	if (CharacterIndex == 0)
	{
		DisplayMesh->SetStaticMesh(Character1Mesh);
	}
	else if (CharacterIndex == 1)
	{
		DisplayMesh->SetStaticMesh(Character2Mesh);
	}

}

