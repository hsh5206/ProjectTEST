// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"

#include "Characters/PTCharacterTypes.h"

#include "PTCharacter.generated.h"

class UGamplayEffect;
class UGameplayAbility;
class UPTAbilitySystemComponent;
class UPTAttributeSet;

UCLASS()
class PROJECTT_API APTCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APTCharacter(const class FObjectInitializer& ObjectInitializer);
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Inventory */
	UPROPERTY(Replicated, EditAnywhere)
	class UInventoryComponent* InventoryComponent;

protected:
	virtual void BeginPlay() override;
	virtual void PawnClientRestart() override;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* Camera;
	class APTPlayerController* PTController;
	class UPTAnimInstance* PTAnimInstance;

	/** Montage */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PT | Animation")
	UAnimMontage* AttackMontage;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PT | Animation")
	UAnimMontage* DeathMontage;

	/** Enhanced Input */
	UPROPERTY(EditDefaultsOnly)
	class UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* MoveInputAction;
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* JumpInputAction;
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* InventoryAction;
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* GetInputAction;

public:
	/** Move */
	FVector CurrentLocation = GetActorLocation();
	bool bIsFirst = false;
	bool bIsMovePressed = false;
	void OnMoveAction();
	void OnMoveActionEnd();
	/** Jump */
	void OnJumpAction();
	void OnJumpActionEnd();
	virtual void Landed(const FHitResult& Hit) override;
	/** Get */
	void GetAction();
	/** Inventory */
	void OnInventoryPressed();

/**
*
* Ability System
*
*/
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// GameplayEffect 적용
	bool ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> Effect, FGameplayEffectContextHandle InEffectContext);

protected:
	UPROPERTY(EditDefaultsOnly)
	UPTAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY(Transient)
	UPTAttributeSet* AttributeSet;

	void GiveAbilities();
	void ApplyStartupEffects();

	// 클라이언트와 서버에서의 초기화를 위함
	virtual void PossessedBy(AController* NewController) override; // 서버
	virtual void OnRep_PlayerState() override; // 클라이언트

	/** Tags */
protected:
	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer InAirTag;
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag JumpEventTag;

/**
*
* Data Assets
*
*/
public:
	UFUNCTION(BlueprintCallable)
	FCharacterData GetCharacterData() const;
	UFUNCTION(BlueprintCallable)
	void SetCharacterData(const FCharacterData& InCharacterData);

protected:
	UPROPERTY(ReplicatedUsing = OnRep_CharacterData)
	FCharacterData CharacterData;

	UFUNCTION()
	void OnRep_CharacterData();

	virtual void InitFromCharacterData(const FCharacterData& InCharacterData, bool bFromReplication = false);

	UPROPERTY(EditDefaultsOnly)
	class UPTCharacterDataAsset* CharacterDataAsset;
};
