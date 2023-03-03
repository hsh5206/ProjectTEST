// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../PTTypes.h"
#include "InventoryList.generated.h"

///////////////////////////////////////////////////////////////////////////

USTRUCT(BlueprintType)
struct FInventoryListItem : public FFastArraySerializerItem
{
	GENERATED_BODY()
public:
	UPROPERTY()
	class UInventoryItemInstance* ItemInstance = nullptr;
};

///////////////////////////////////////////////////////////////////////////

USTRUCT(BlueprintType)
struct FInventoryList : public FFastArraySerializer
{
	GENERATED_BODY()
	
public:
	// ���ø�����Ʈ �Ҷ� �̸� ���ؼ� ����
	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FInventoryListItem, FInventoryList>(Items, DeltaParams, *this);
	}

	/** �߰� ���� */
	void AddItem(TSubclassOf<UItemStaticData> InItemStaticDataClass);
	void RemoveItem(TSubclassOf<UItemStaticData> OutItemStaticDataClass);

	TArray<FInventoryListItem> GetItemRef() { return Items; }

protected:
	UPROPERTY()
	TArray<FInventoryListItem> Items;
};

///////////////////////////////////////////////////////////////////////////

// �������� FInventoryList struct �� Ŀ���� �ø�������� �Լ��� ���������� �˸�
template<>
struct TStructOpsTypeTraits<FInventoryList> : public TStructOpsTypeTraitsBase2<FInventoryList>
{
	enum
	{
		WithNetDeltaSerializer = true
	};
};
// Traits -> ��Ÿ�ӿ��� ������Ÿ������ (��Ÿ�� ������带 ���̴� �����ս� ��� ����)