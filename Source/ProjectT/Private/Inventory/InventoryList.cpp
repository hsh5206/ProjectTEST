// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryList.h"
#include "Inventory/InventoryItemInstance.h"

void FInventoryList::AddItem(TSubclassOf<class UItemStaticData> InItemStaticDataClass)
{
	FInventoryListItem& Item = Items.AddDefaulted_GetRef(); // �迭�� �������� ����Ʈ�� �߰�
	Item.ItemInstance = NewObject<UInventoryItemInstance>(); // ����
	Item.ItemInstance->Init(InItemStaticDataClass); // �ʱ�ȭ
	MarkItemDirty(Item); // �迭�� ��ȭ�� �������� ȣ���ؾ���
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
