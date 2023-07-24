// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "../Data/NormalMonsterState.h"
#include "NormalMonsterData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct UE5_PORTFOLIO_API FNormalMonsterData : public FTableRowBase
{
	GENERATED_BODY()
	
	FNormalMonsterData()
	{

	}

	~FNormalMonsterData()
	{

	}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int ATT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float SearchRange = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TMap<NormalMonsterState, class UAnimMontage*> NormalMonsterAnims;
};
