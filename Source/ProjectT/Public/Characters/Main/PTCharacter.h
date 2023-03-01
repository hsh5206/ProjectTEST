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

	// 세션 생성 델리게이트 콜백
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccesful);
	// 세션 찾기 델리게이트 콜백
	void OnFindSessionsComplete(bool bWasSuccesful);
	// 세션 참가 델리게이트 콜백
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

private:
	// 세션 생성 델리게이트
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	// 세션 찾기 델리게이트
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	// 세션 참가 델리게이트
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
	// 세션 찾기 결과Arr
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
};
