// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "InventoryComponent.generated.h"


UCLASS(editinlinenew, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

public:
	class UInventoryWidget* InventoryWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class TSubclassOf<UInventoryWidget> InventoryWidgetClass;
	void ToggleInventory();

	UPROPERTY(VisibleAnywhere)
	TArray<TSubclassOf<class AItemBase>> Inventory;

	void AddItem(class AItemBase* Item);
};
