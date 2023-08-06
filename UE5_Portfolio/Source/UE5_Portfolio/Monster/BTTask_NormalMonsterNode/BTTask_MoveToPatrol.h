// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_MoveToPatrol.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API UBTTask_MoveToPatrol : public UBTTask_MoveTo
{
	GENERATED_BODY()
	
public:

	UBTTask_MoveToPatrol();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	UBlackboardComponent* GetBlackboardComponent(UBehaviorTreeComponent& OwnerComp);

	class ANormalMonster* GetNormalMonster(UBehaviorTreeComponent& OwnerComp);
};
