// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTT_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual bool Initialize() override;

public:
	void UpdateInventory(TArray<TSubclassOf<class AItemBase>> Inventory);

	class UInventorySlot* InventorySlot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class TSubclassOf<UInventorySlot> InventorySlotClass;

	/** πŸ¿ŒµÂ */
	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* Grid;
};
