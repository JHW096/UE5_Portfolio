// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../Global/Data/ItemData.h"
#include "ItemObj.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API UItemObj : public UObject
{
	GENERATED_BODY()

public:

	const FItemData* ItemData;

};
