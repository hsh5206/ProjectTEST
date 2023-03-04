// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InventoryWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/Image.h"

#include "Widget/InventorySlot.h"
#include "Items/ItemBase.h"



bool UInventoryWidget::Initialize()
{
	bool bWrote = Super::Initialize();

	return bWrote;
}

void UInventoryWidget::UpdateInventory(TArray<TSubclassOf<class AItemBase>> Inventory)
{
	if (InventorySlotClass)
	{
		for (auto Item : Inventory)
		{
			InventorySlot = CreateWidget<UInventorySlot>(GetWorld(), InventorySlotClass); \
			InventorySlot->ItemIcon->SetBrushFromTexture(Item.GetDefaultObject()->Icon);
			Grid->AddChild(InventorySlot);
		}
	}
}
