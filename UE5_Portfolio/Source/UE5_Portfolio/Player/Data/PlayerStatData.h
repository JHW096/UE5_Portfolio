// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "PlayerStatData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct UE5_PORTFOLIO_API FPlayerStatData : public FTableRowBase
{
	GENERATED_BODY()

	FPlayerStatData() { }
	~FPlayerStatData() { }


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 MaxHp = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 MaxMp = 100;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 FristBulletPower = 2; // 3-> 4 -> 5

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 SecondBulletPower = 3;  // -> 5 - > 7 -> 9

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 ThirdBulletPower = 5; // 8 -> 11 -> 14

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 SnipeShootPower = 15;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 SnipeShootMp = 20;
	
	//TODO
	//Other Skills Power, MP..
	
};

