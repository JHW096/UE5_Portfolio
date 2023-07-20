// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AINormalMonster.h"
#include "../Data/NormalMonsterState.h"
#include "MeleeMonster.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API AMeleeMonster : public AAINormalMonster
{
	GENERATED_BODY()

	AMeleeMonster();

	void BeginPlay() override;
	
	const struct FNormalMonsterData* NormalMonsterData;

private:

	UPROPERTY(Category = "MeleeInfo", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName MeleeMonsterName = "NONE";
};
