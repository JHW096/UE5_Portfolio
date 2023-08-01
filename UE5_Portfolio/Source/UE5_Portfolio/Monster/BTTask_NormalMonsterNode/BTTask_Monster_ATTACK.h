// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTask_NormalMonsterBaseNode.h"
#include "BTTask_Monster_ATTACK.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API UBTTask_Monster_ATTACK : public UBTTask_NormalMonsterBaseNode
{
	GENERATED_BODY()

	UBTTask_Monster_ATTACK();

protected:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds);

};
