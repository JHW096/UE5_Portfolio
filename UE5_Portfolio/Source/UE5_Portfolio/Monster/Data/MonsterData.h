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
	int HP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int ATT = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float SearchRange = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float AttackRange = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FVector SpawnPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TMap<NormalMonsterState, class UAnimMontage*> NormalMonsterAnims;
};
