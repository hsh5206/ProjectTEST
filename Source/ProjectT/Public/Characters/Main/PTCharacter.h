// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"

#include "Characters/PTCharacterTypes.h"

#include "Interfaces/OnlineSessionInterface.h"

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
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;
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

public:
	/** Move */
	FVector CurrentLocation = GetActorLocation();
	bool bIsFirst = false;
	void Move();
	void MoveEnd();
	bool bIsMovePressed = false;


/**
*
* Ability System
*
*/
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// GameplayEffect ����
	bool ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> Effect, FGameplayEffectContextHandle InEffectContext);

protected:
	UPROPERTY(EditDefaultsOnly)
	UPTAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY(Transient)
	UPTAttributeSet* AttributeSet;

	void GiveAbilities();
	void ApplyStartupEffects();

	// Ŭ���̾�Ʈ�� ���������� �ʱ�ȭ�� ����
	virtual void PossessedBy(AController* NewController) override; // ����
	virtual void OnRep_PlayerState() override; // Ŭ���̾�Ʈ

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

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps);

/** 
*
* Online Subsystem
*
*/
public:
	IOnlineSessionPtr OnlineSessionInterface;
protected:
	UFUNCTION(BlueprintCallable)
	void CreateGameSession();
	UFUNCTION(BlueprintCallable)
	void FindGameSessions();

	// ���� ���� ��������Ʈ �ݹ�
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccesful);
	// ���� ã�� ��������Ʈ �ݹ�
	void OnFindSessionsComplete(bool bWasSuccesful);
	// ���� ���� ��������Ʈ �ݹ�
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

private:
	// ���� ���� ��������Ʈ
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	// ���� ã�� ��������Ʈ
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	// ���� ���� ��������Ʈ
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
	// ���� ã�� ���Arr
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
};
