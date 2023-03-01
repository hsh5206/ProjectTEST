// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "PTAbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FReceivedDamageDelegate, UPTAbilitySystemComponent*, SourceASC, float, UnmitigateDamage, float, MitigatedDamage);

/**
 * 
 */
UCLASS()
class PROJECTT_API UPTAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	bool CharacterAbilitiesGiven = false;
	bool StartupEffectsApplied = false;

	FReceivedDamageDelegate OnReceiveDamage;

	virtual void ReceiveDamage(UPTAbilitySystemComponent* SourceASC, float UnmitigateDamage, float MitigatedDamage);
};
