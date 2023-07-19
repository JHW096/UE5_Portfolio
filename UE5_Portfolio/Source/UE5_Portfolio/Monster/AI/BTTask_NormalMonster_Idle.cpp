// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_NormalMonster_Idle.h"

UBTTask_NormalMonster_Idle::UBTTask_NormalMonster_Idle()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

void UBTTask_NormalMonster_Idle::OnGameplayTaskActivated(UGameplayTask&)
{
	
}

EBTNodeResult::Type UBTTask_NormalMonster_Idle::ExecuteTask(UBehaviorTree& OwnerComp, uint8* NodeMemory)
{

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_NormalMonster_Idle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	return;
}
