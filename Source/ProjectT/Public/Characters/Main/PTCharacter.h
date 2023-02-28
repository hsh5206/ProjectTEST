// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PTCharacter.generated.h"

UCLASS()
class PROJECTT_API APTCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APTCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* Camera;
	class APTPlayerController* PTController;
	class UPTAnimInstance* PTAnimInstance;

public:
	

	FVector CurrentLocation = GetActorLocation();
	bool bIsFirst = false;

	/** Inform of AnimInstance */


	/** Input Value */
	bool bIsMovePressed = false;

	/** Input Callback */
	void Move();
	void MoveEnd();
	void Attack();

	/** Montage */
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* AttackMontage;
};
