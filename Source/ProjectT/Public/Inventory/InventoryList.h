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
	// 리플리케이트 할때 이를 통해서 수행
	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FInventoryListItem, FInventoryList>(Items, DeltaParams, *this);
	}

	/** 추가 제거 */
	void AddItem(TSubclassOf<UItemStaticData> InItemStaticDataClass);
	void RemoveItem(TSubclassOf<UItemStaticData> OutItemStaticDataClass);

	TArray<FInventoryListItem> GetItemRef() { return Items; }

protected:
	UPROPERTY()
	TArray<FInventoryListItem> Items;
};

///////////////////////////////////////////////////////////////////////////

// 엔진에게 FInventoryList struct 가 커스텀 시리얼라이즈 함수로 구현됐음을 알림
template<>
struct TStructOpsTypeTraits<FInventoryList> : public TStructOpsTypeTraitsBase2<FInventoryList>
{
	enum
	{
		WithNetDeltaSerializer = true
	};
};
// Traits -> 런타임에서 컴파일타임으로 (런타임 오버헤드를 줄이는 퍼포먼스 향상 도출)