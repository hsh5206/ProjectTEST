// Fill out your copyright notice in the Description page of Project Settings.


#include "PTGameInstance.h"

#include "AbilitySystemGlobals.h"

void UPTGameInstance::Init()
{
	Super::Init();

	// �۷ι� ������ ���̺� �� �±׸� �ε��Ϸ��� ������Ʈ ������ �Ϻη� �� �� ȣ���ؾ� ��
	UAbilitySystemGlobals::Get().InitGlobalData();
}
