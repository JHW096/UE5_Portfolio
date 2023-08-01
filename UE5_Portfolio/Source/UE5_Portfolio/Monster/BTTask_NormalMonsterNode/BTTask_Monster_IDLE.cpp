// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Monster_IDLE.h"



UBTTask_Monster_IDLE::UBTTask_Monster_IDLE()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
	
}

EBTNodeResult::Type UBTTask_Monster_IDLE::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	GetNormalMonster(OwnerComp)->SetAnimState(NormalMonsterState::IDLE);
	
	return EBTNodeResult::InProgress;
}

void UBTTask_Monster_IDLE::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	int a = 0;

	AActor* TargetActor = GetTargetSearch(OwnerComp);

	if (TargetActor != nullptr)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), TargetActor);
		SetNormalMonsterState(OwnerComp, NormalMonsterState::MOVE);
		return;
	}

	return;
}
