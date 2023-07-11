// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "TestData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct UE5_PORTFOLIO_API FTestData : public FTableRowBase
{
	GENERATED_BODY()

	FTestData() { }
	~FTestData() { }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TestData")
	float value = 10;
};
