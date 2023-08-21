// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../Global/Data/ItemData.h"
#include "InvenItemData.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API UInvenItemData : public UObject
{
	GENERATED_BODY()

public:

	class UItemSlot* m_SlotWidget;

	const FItemData* m_ItemData;

	int Count = 1;

};


