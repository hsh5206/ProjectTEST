// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include <ProjectT/ProjectT.h>
#include "PTGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTT_API UPTGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UPTGameplayAbility();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);

protected:
	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TArray<TSubclassOf<UGameplayEffect>> OngoingEffectsToRemoveOnEnd;
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TArray<TSubclassOf<UGameplayEffect>> OngoingEffectsToJustApplyOnStart;

	TArray<FActiveGameplayEffectHandle> RemoveOnEndEffetHandles;

	UFUNCTION(blueprintCallable, BlueprintPure)
	class APTCharacter* GetPTCharacterFromActorInfo() const;
};
