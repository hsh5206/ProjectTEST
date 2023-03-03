// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GA_Jump.h"
#include "GameFramework/Character.h"

#include "AbilitySystemComponent.h"

UGA_Jump::UGA_Jump()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted; // 로컬->서버 실행
	InstancingPolicy = EGameplayAbilityInstancingPolicy::NonInstanced; // 인스턴스화X 자주사용되는 간단한 어빌리티
}

bool UGA_Jump::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags)) return false;

	const ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get(), ECastCheckedType::NullAllowed);
	return Character->CanJump();
}

void UGA_Jump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		if (!CommitAbility(Handle, ActorInfo, ActivationInfo)) return;

		Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

		ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get());
		Character->Jump();
	}
}
