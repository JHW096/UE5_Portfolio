// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NormalMonster.h"
#include "AINormalMonster.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API AAINormalMonster : public ANormalMonster
{
	GENERATED_BODY()
	
public:

	FORCEINLINE class UBehaviorTree* GetBehaviorTree()
	{
		return BehaviorTree;
	}

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree")
	class UBehaviorTree* BehaviorTree;
};
