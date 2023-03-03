// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PTAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTT_API UPTAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
	class APTCharacter* Character;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	class UCharacterMovementComponent* Movement;

	UPROPERTY(BlueprintReadWrite)
	float Speed = 0.f;
	UPROPERTY(BlueprintReadOnly)
	bool bIsInAir = false;
};
