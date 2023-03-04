// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemBase.h"

#include "Components/SphereComponent.h"
#include "characters/Main/PTCharacter.h"

#include "Inventory/InventoryComponent.h"

AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (ItemMesh)
	{
		Mesh->SetStaticMesh(ItemMesh);
	}

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnSphereOverlapEnd);

}

void AItemBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APTCharacter* Character = Cast<APTCharacter>(OtherActor))
	{
		Character->InventoryComponent->AddItem(this);
		Destroy();
	}

}

void AItemBase::OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}