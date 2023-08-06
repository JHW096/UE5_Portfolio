// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTask_NormalMonsterBaseNode.h"
#include "BTTask_Monster_PATROL.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API UBTTask_Monster_PATROL : public UBTTask_NormalMonsterBaseNode
{
	GENERATED_BODY()

	UBTTask_Monster_PATROL();

protected:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	//void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

};
