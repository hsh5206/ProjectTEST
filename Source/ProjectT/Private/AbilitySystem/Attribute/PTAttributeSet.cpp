// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attribute/PTAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

void UPTAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPTAttributeSet, Health, OldHealth);
}

void UPTAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPTAttributeSet, MaxHealth, OldMaxHealth);
}

//  리플리케이트할 속성 등록 (#include "Net/UnrealNetwork.h")
void UPTAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 리플리케이트 추가
	DOREPLIFETIME_CONDITION_NOTIFY(UPTAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPTAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

// GameplayEffect가 실행되기 직전에 호출
void UPTAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	// 프로퍼티 게터를 사용하여 이 호출이 Health에 영향을 미치는지 확인
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Health의 값을 0~MaxHealth로
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
}
