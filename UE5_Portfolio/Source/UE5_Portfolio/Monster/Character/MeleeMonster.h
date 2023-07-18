// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AINormalMonster.h"
#include "../Data/NormalMonsterData.h"
#include "MeleeMonster.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API AMeleeMonster : public AAINormalMonster
{
	GENERATED_BODY()


	const FNormalMonsterData* CurMonsterData;
};
