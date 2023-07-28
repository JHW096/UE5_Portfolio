// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "UI_Data.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct UE5_PORTFOLIO_API FUI_Data : public FTableRowBase
{
	GENERATED_BODY()

	FUI_Data() { }
	~FUI_Data() { }

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TSubclassOf<UObject> Object;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI_Data")
	TSubclassOf<UObject> WBP_Widget;
};
