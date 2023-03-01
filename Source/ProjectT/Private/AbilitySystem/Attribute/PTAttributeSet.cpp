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

//  ���ø�����Ʈ�� �Ӽ� ��� (#include "Net/UnrealNetwork.h")
void UPTAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// ���ø�����Ʈ �߰�
	DOREPLIFETIME_CONDITION_NOTIFY(UPTAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPTAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

// GameplayEffect�� ����Ǳ� ������ ȣ��
void UPTAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	// ������Ƽ ���͸� ����Ͽ� �� ȣ���� Health�� ������ ��ġ���� Ȯ��
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Health�� ���� 0~MaxHealth��
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
}
