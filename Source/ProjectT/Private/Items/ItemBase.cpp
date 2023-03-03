// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemBase.h"
#include "Engine/ActorChannel.h"
#include "Net/UnrealNetwork.h"

#include "Inventory/InventoryItemInstance.h"

AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AItemBase::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	wroteSomething = Channel->ReplicateSubobject(ItemInstance, *Bunch, *RepFlags);

	return wroteSomething;
}

void AItemBase::Init(UInventoryItemInstance* InItemInstance)
{
	ItemInstance = InItemInstance;
}

void AItemBase::OnEquipped()
{
}

void AItemBase::OnUnequipped()
{
}

void AItemBase::OnDropped()
{
}


void AItemBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AItemBase, ItemInstance);
}