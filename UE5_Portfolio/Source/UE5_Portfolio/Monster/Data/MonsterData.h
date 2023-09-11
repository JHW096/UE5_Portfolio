// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "../Data/NormalMonsterState.h"
#include "MonsterData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct UE5_PORTFOLIO_API FMonsterData : public FTableRowBase
{
	GENERATED_BODY()
	
	FMonsterData() { }

	~FMonsterData() { }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 MaxHp = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 OffensivePower = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float SearchRange = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float AttackRange = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float RangeOver = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FVector SpawnPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TMap<NormalMonsterState, class UAnimMontage*> NormalMonsterAnims;
};
