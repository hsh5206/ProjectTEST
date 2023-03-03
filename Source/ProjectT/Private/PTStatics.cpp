// Fill out your copyright notice in the Description page of Project Settings.


#include "PTStatics.h"

const UItemStaticData* UPTStatics::GetItemStaticData(TSubclassOf<UItemStaticData> ItaemDataClass)
{
	if (IsValid(ItaemDataClass))
	{
		return GetDefault<UItemStaticData>(ItaemDataClass);
	}

	return nullptr;
}
