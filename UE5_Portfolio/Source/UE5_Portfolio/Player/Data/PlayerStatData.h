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
	int a = 0;

	int32 Level = 1;

	int32 MaxHp = 100;

	int32 MaxMp = 100;
	
	int32 FristBulletPower = 2; // 3-> 4 -> 5

	int32 SecondBulletPower = 3;  // -> 5 - > 7 -> 9

	int32 ThirdBulletPower = 5; // 8 -> 11 -> 14

	int32 SnipeShootPower = 15;

	int32 SnipeShootMp = 20;
	
	//TODO
	//Other Skills Power, MP..
	
};

