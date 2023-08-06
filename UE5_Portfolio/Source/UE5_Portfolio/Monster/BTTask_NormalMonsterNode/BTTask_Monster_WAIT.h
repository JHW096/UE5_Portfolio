// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_Wait.h"
#include "BTTask_Monster_WAIT.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API UBTTask_Monster_WAIT : public UBTTask_Wait
{
	GENERATED_BODY()
	
	UBTTask_Monster_WAIT();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	UBlackboardComponent* GetBlackboardComponent(UBehaviorTreeComponent& OwnerComp);

	class ANormalMonster* GetNormalMonster(UBehaviorTreeComponent& OwnerComp);
};
