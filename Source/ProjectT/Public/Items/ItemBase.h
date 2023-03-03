// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

UCLASS()
class PROJECTT_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemBase();
	virtual void Tick(float DeltaTime) override;
	virtual bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	void Init(class UInventoryItemInstance* InItemInstance);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(Replicated)
	class UInventoryItemInstance* ItemInstance = nullptr;

public:	
	virtual void OnEquipped();
	virtual void OnUnequipped();
	virtual void OnDropped();
};
