// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Main/PTAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Characters/Main/PTCharacter.h"

void UPTAnimInstance::NativeInitializeAnimation()
{
	Character = Cast<APTCharacter>(TryGetPawnOwner());
	if (Character)
	{
		Movement = Character->GetCharacterMovement();
	}
}

void UPTAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (Movement)
	{
		Speed = Movement->Velocity.Size();
		bIsInAir = Movement->IsFalling();
	}
}