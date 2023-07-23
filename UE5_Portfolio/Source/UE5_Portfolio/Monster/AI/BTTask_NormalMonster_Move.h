// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_BaseNode.h"
#include "BTTask_NormalMonster_Move.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API UBTTask_NormalMonster_Move : public UBTTask_BaseNode
{
	GENERATED_BODY()


	UBTTask_NormalMonster_Move();

protected:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

};
