// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "Test2.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct UE5_PORTFOLIO_API FTest2 : public FTableRowBase
{
	GENERATED_BODY()

	FTest2() { }
	~FTest2() { }

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TSubclassOf<class UUserWidget> Objects;
	
};
