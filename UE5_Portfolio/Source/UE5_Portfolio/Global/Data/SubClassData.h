// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SubClassData.generated.h"


/**
 * 
 */
USTRUCT(BlueprintType)
struct UE5_PORTFOLIO_API FSubClassData : public FTableRowBase
{ 
	GENERATED_BODY()

public:

	FSubClassData() { }
	~FSubClassData() { }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TSubclassOf<UObject> Object;
};
