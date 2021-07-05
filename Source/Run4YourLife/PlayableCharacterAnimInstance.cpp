// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacterAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "PlayableCharacter.h"

void UPlayableCharacterAnimInstance::NativeInitializeAnimation()
{
	if (PlayerPawn == nullptr)
	{
		PlayerPawn = TryGetPawnOwner();
	}
}

void UPlayableCharacterAnimInstance::UpdateAnimationProperties()
{
	if (PlayerPawn == nullptr)
	{
		PlayerPawn = TryGetPawnOwner();
	}

	if (PlayerPawn)
	{
		FVector PlayerSpeed = PlayerPawn->GetVelocity();
		FVector LateralSpeed = FVector(PlayerSpeed.X, PlayerSpeed.Y, 0);
		CharacterMoveSpeed = LateralSpeed.Size();

		bIsJumping = PlayerPawn->GetMovementComponent()->IsFalling();
	}
}