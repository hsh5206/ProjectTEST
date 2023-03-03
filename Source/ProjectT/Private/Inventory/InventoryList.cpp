// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryList.h"
#include "Inventory/InventoryItemInstance.h"

void FInventoryList::AddItem(TSubclassOf<class UItemStaticData> InItemStaticDataClass)
{
	FInventoryListItem& Item = Items.AddDefaulted_GetRef(); // 배열의 마지막에 디폴트로 추가
	Item.ItemInstance = NewObject<UInventoryItemInstance>(); // 생성
	Item.ItemInstance->Init(InItemStaticDataClass); // 초기화
	MarkItemDirty(Item); // 배열에 변화가 생겼을때 호출해야함
}

void FInventoryList::RemoveItem(TSubclassOf<class UItemStaticData> OutItemStaticDataClass)
{
	for (auto ItemIter = Items.CreateIterator(); ItemIter; ++ItemIter)
	{
		FInventoryListItem Item = *ItemIter;
		if (Item.ItemInstance && Item.ItemInstance->IsA(OutItemStaticDataClass))
		{
			ItemIter.RemoveCurrent();
			MarkArrayDirty();
			break;
		}
	}
}
