// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/PTGameplayAbility.h"
#include "AbilitySystem/Components/PTAbilitySystemComponent.h"

#include "Characters/Main/PTCharacter.h"

UPTGameplayAbility::UPTGameplayAbility()
{

}

void UPTGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	FGameplayEffectContextHandle EffectContext = ActorInfo->AbilitySystemComponent->MakeEffectContext();

	for (auto GameplayEffect : OngoingEffectsToJustApplyOnStart)
	{
		if (!GameplayEffect.Get()) continue;

		if (UAbilitySystemComponent* AbilitySystem = ActorInfo->AbilitySystemComponent.Get())
		{
			FGameplayEffectSpecHandle SpecHandle = AbilitySystem->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
			if (SpecHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystem->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
				if (!ActiveGEHandle.WasSuccessfullyApplied())
				{
					ABILITY_LOG(Log, TEXT("Ability %s failed to apply startup effect %s"), *GetName(), *GetNameSafe(GameplayEffect));
				}
			}
		}
	}

	if (IsInstantiated())
	{
		for (auto GameplayEffect : OngoingEffectsToRemoveOnEnd)
		{
			if (!GameplayEffect.Get()) continue;

			if (UAbilitySystemComponent* AbilitySystem = ActorInfo->AbilitySystemComponent.Get())
			{
				FGameplayEffectSpecHandle SpecHandle = AbilitySystem->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
				if (SpecHandle.IsValid())
				{
					FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystem->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
					if (!ActiveGEHandle.WasSuccessfullyApplied())
					{
						ABILITY_LOG(Log, TEXT("Ability %s failed to apply runtime effect %s"), *GetName(), *GetNameSafe(GameplayEffect));
					}
					else
					{
						RemoveOnEndEffetHandles.Add(ActiveGEHandle);
					}
				}
			}
		}
	}
}

void UPTGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (IsInstantiated())
	{
		for (FActiveGameplayEffectHandle ActiveEffectHandle : RemoveOnEndEffetHandles)
		{
			if (ActiveEffectHandle.IsValid())
			{
				ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(ActiveEffectHandle);
			}
		}

		RemoveOnEndEffetHandles.Empty();
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

APTCharacter* UPTGameplayAbility::GetPTCharacterFromActorInfo() const
{
	return Cast<APTCharacter>(GetAvatarActorFromActorInfo());
}

