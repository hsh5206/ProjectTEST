// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Characters/PTCharacterTypes.h"
#include "PTCharacterDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PROJECTT_API UPTCharacterDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FCharacterData CharacterData;
};
