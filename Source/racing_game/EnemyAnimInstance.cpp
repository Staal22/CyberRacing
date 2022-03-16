// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAnimInstance.h"
#include "Enemy.h"

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	if (EnemyRef == nullptr)
	{
		EnemyRef = TryGetPawnOwner();
	}
}

void UEnemyAnimInstance::UpdateAnimationProperties()
{
	if (EnemyRef == nullptr)
	{
		EnemyRef = TryGetPawnOwner();
	}

	if (EnemyRef)
	{
		FVector TempSpeed = EnemyRef->GetVelocity();
		FVector LateralSpeed = FVector(TempSpeed.X, TempSpeed.Y, 0.f);
		MovementSpeed = LateralSpeed.Size();
	}
}
