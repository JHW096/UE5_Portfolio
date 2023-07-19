// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_NormalMonster_Move.h"

UBTTask_NormalMonster_Move::UBTTask_NormalMonster_Move()
{

}
 
void UBTTask_NormalMonster_Move::OnGameplayTaskActivated(UGameplayTask&)
{
}

EBTNodeResult::Type UBTTask_NormalMonster_Move::ExecuteTask(UBehaviorTree& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Type();
}

void UBTTask_NormalMonster_Move::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
}
